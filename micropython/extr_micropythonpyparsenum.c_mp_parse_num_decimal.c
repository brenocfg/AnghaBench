#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  mp_obj_t ;
typedef  int /*<<< orphan*/  mp_lexer_t ;

/* Variables and functions */
 int /*<<< orphan*/  mp_obj_new_exception_msg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  mp_type_ValueError ; 
 int /*<<< orphan*/  raise_exc (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

mp_obj_t mp_parse_num_decimal(const char *str, size_t len, bool allow_imag, bool force_complex, mp_lexer_t *lex) {
#if MICROPY_PY_BUILTINS_FLOAT

// DEC_VAL_MAX only needs to be rough and is used to retain precision while not overflowing
// SMALL_NORMAL_VAL is the smallest power of 10 that is still a normal float
// EXACT_POWER_OF_10 is the largest value of x so that 10^x can be stored exactly in a float
//   Note: EXACT_POWER_OF_10 is at least floor(log_5(2^mantissa_length)). Indeed, 10^n = 2^n * 5^n
//   so we only have to store the 5^n part in the mantissa (the 2^n part will go into the float's
//   exponent).
#if MICROPY_FLOAT_IMPL == MICROPY_FLOAT_IMPL_FLOAT
#define DEC_VAL_MAX 1e20F
#define SMALL_NORMAL_VAL (1e-37F)
#define SMALL_NORMAL_EXP (-37)
#define EXACT_POWER_OF_10 (9)
#elif MICROPY_FLOAT_IMPL == MICROPY_FLOAT_IMPL_DOUBLE
#define DEC_VAL_MAX 1e200
#define SMALL_NORMAL_VAL (1e-307)
#define SMALL_NORMAL_EXP (-307)
#define EXACT_POWER_OF_10 (22)
#endif

    const char *top = str + len;
    mp_float_t dec_val = 0;
    bool dec_neg = false;
    bool imag = false;

    // skip leading space
    for (; str < top && unichar_isspace(*str); str++) {
    }

    // parse optional sign
    if (str < top) {
        if (*str == '+') {
            str++;
        } else if (*str == '-') {
            str++;
            dec_neg = true;
        }
    }

    const char *str_val_start = str;

    // determine what the string is
    if (str < top && (str[0] | 0x20) == 'i') {
        // string starts with 'i', should be 'inf' or 'infinity' (case insensitive)
        if (str + 2 < top && (str[1] | 0x20) == 'n' && (str[2] | 0x20) == 'f') {
            // inf
            str += 3;
            dec_val = INFINITY;
            if (str + 4 < top && (str[0] | 0x20) == 'i' && (str[1] | 0x20) == 'n' && (str[2] | 0x20) == 'i' && (str[3] | 0x20) == 't' && (str[4] | 0x20) == 'y') {
                // infinity
                str += 5;
            }
        }
    } else if (str < top && (str[0] | 0x20) == 'n') {
        // string starts with 'n', should be 'nan' (case insensitive)
        if (str + 2 < top && (str[1] | 0x20) == 'a' && (str[2] | 0x20) == 'n') {
            // NaN
            str += 3;
            dec_val = MICROPY_FLOAT_C_FUN(nan)("");
        }
    } else {
        // string should be a decimal number
        parse_dec_in_t in = PARSE_DEC_IN_INTG;
        bool exp_neg = false;
        int exp_val = 0;
        int exp_extra = 0;
        while (str < top) {
            unsigned int dig = *str++;
            if ('0' <= dig && dig <= '9') {
                dig -= '0';
                if (in == PARSE_DEC_IN_EXP) {
                    // don't overflow exp_val when adding next digit, instead just truncate
                    // it and the resulting float will still be correct, either inf or 0.0
                    // (use INT_MAX/2 to allow adding exp_extra at the end without overflow)
                    if (exp_val < (INT_MAX / 2 - 9) / 10) {
                        exp_val = 10 * exp_val + dig;
                    }
                } else {
                    if (dec_val < DEC_VAL_MAX) {
                        // dec_val won't overflow so keep accumulating
                        dec_val = 10 * dec_val + dig;
                        if (in == PARSE_DEC_IN_FRAC) {
                            --exp_extra;
                        }
                    } else {
                        // dec_val might overflow and we anyway can't represent more digits
                        // of precision, so ignore the digit and just adjust the exponent
                        if (in == PARSE_DEC_IN_INTG) {
                            ++exp_extra;
                        }
                    }
                }
            } else if (in == PARSE_DEC_IN_INTG && dig == '.') {
                in = PARSE_DEC_IN_FRAC;
            } else if (in != PARSE_DEC_IN_EXP && ((dig | 0x20) == 'e')) {
                in = PARSE_DEC_IN_EXP;
                if (str < top) {
                    if (str[0] == '+') {
                        str++;
                    } else if (str[0] == '-') {
                        str++;
                        exp_neg = true;
                    }
                }
                if (str == top) {
                    goto value_error;
                }
            } else if (allow_imag && (dig | 0x20) == 'j') {
                imag = true;
                break;
            } else if (dig == '_') {
                continue;
            } else {
                // unknown character
                str--;
                break;
            }
        }

        // work out the exponent
        if (exp_neg) {
            exp_val = -exp_val;
        }

        // apply the exponent, making sure it's not a subnormal value
        exp_val += exp_extra;
        if (exp_val < SMALL_NORMAL_EXP) {
            exp_val -= SMALL_NORMAL_EXP;
            dec_val *= SMALL_NORMAL_VAL;
        }

        // At this point, we need to multiply the mantissa by its base 10 exponent. If possible,
        // we would rather manipulate numbers that have an exact representation in IEEE754. It
        // turns out small positive powers of 10 do, whereas small negative powers of 10 don't.
        // So in that case, we'll yield a division of exact values rather than a multiplication
        // of slightly erroneous values.
        if (exp_val < 0 && exp_val >= -EXACT_POWER_OF_10) {
            dec_val /= MICROPY_FLOAT_C_FUN(pow)(10, -exp_val);
        } else {
            dec_val *= MICROPY_FLOAT_C_FUN(pow)(10, exp_val);
        }
    }

    // negate value if needed
    if (dec_neg) {
        dec_val = -dec_val;
    }

    // check we parsed something
    if (str == str_val_start) {
        goto value_error;
    }

    // skip trailing space
    for (; str < top && unichar_isspace(*str); str++) {
    }

    // check we reached the end of the string
    if (str != top) {
        goto value_error;
    }

    // return the object
#if MICROPY_PY_BUILTINS_COMPLEX
    if (imag) {
        return mp_obj_new_complex(0, dec_val);
    } else if (force_complex) {
        return mp_obj_new_complex(dec_val, 0);
    }
#else
    if (imag || force_complex) {
        raise_exc(mp_obj_new_exception_msg(&mp_type_ValueError, "complex values not supported"), lex);
    }
#endif
    else {
        return mp_obj_new_float(dec_val);
    }

value_error:
    raise_exc(mp_obj_new_exception_msg(&mp_type_ValueError, "invalid syntax for number"), lex);

#else
    raise_exc(mp_obj_new_exception_msg(&mp_type_ValueError, "decimal numbers not supported"), lex);
#endif
}
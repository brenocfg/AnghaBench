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
typedef  int uint8_t ;

/* Variables and functions */
 int NN_SWS_UTF8_FRAGMENT ; 
 int NN_SWS_UTF8_INVALID ; 
 int /*<<< orphan*/  nn_assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nn_utf8_code_point (const uint8_t *buffer, size_t len)
{
    /*  The lack of information is considered neither valid nor invalid. */
    if (!buffer || !len)
        return NN_SWS_UTF8_FRAGMENT;

    /*  RFC 3629 section 4 UTF8-1. */
    if (buffer [0] <= 0x7F)
        return 1;

    /*  0xC2, or 11000001, is the smallest conceivable multi-octet code
        point that is not an illegal overlong encoding. */
    if (buffer [0] < 0xC2)
        return NN_SWS_UTF8_INVALID;

    /*  Largest 2-octet code point starts with 0xDF (11011111). */
    if (buffer [0] <= 0xDF) {
        if (len < 2)
            return NN_SWS_UTF8_FRAGMENT;
        /*  Ensure continuation byte in form of 10xxxxxx */
        else if ((buffer [1] & 0xC0) != 0x80)
            return NN_SWS_UTF8_INVALID;
        else
            return 2;
    }

    /*  RFC 3629 section 4 UTF8-3, where 0xEF is 11101111. */
    if (buffer [0] <= 0xEF) {
        /*  Fragment. */
        if (len < 2)
            return NN_SWS_UTF8_FRAGMENT;
        /*  Illegal overlong sequence detection. */
        else if (buffer [0] == 0xE0 && (buffer [1] < 0xA0 || buffer [1] == 0x80))
            return NN_SWS_UTF8_INVALID;
        /*  Illegal UTF-16 surrogate pair half U+D800 through U+DFFF. */
        else if (buffer [0] == 0xED && buffer [1] >= 0xA0)
            return NN_SWS_UTF8_INVALID;
        /*  Fragment. */
        else if (len < 3)
            return NN_SWS_UTF8_FRAGMENT;
        /*  Ensure continuation bytes 2 and 3 in form of 10xxxxxx */
        else if ((buffer [1] & 0xC0) != 0x80 || (buffer [2] & 0xC0) != 0x80)
            return NN_SWS_UTF8_INVALID;
        else
            return 3;
    }

    /*  RFC 3629 section 4 UTF8-4, where 0xF4 is 11110100. Why
        not 11110111 to follow the pattern? Because UTF-8 encoding
        stops at 0x10FFFF as per RFC 3629. */
    if (buffer [0] <= 0xF4) {
        /*  Fragment. */
        if (len < 2)
            return NN_SWS_UTF8_FRAGMENT;
        /*  Illegal overlong sequence detection. */
        else if (buffer [0] == 0xF0 && buffer [1] < 0x90)
            return NN_SWS_UTF8_INVALID;
        /*  Illegal code point greater than U+10FFFF. */
        else if (buffer [0] == 0xF4 && buffer [1] >= 0x90)
            return NN_SWS_UTF8_INVALID;
        /*  Fragment. */
        else if (len < 4)
            return NN_SWS_UTF8_FRAGMENT;
        /*  Ensure continuation bytes 2, 3, and 4 in form of 10xxxxxx */
        else if ((buffer [1] & 0xC0) != 0x80 ||
            (buffer [2] & 0xC0) != 0x80 ||
            (buffer [3] & 0xC0) != 0x80)
            return NN_SWS_UTF8_INVALID;
        else
            return 4;
    }

    /*  UTF-8 encoding stops at U+10FFFF and only defines up to 4-octet
        code point sequences. */
    if (buffer [0] >= 0xF5)
        return NN_SWS_UTF8_INVALID;

    /*  Algorithm error; a case above should have been satisfied. */
    nn_assert (0);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  len; scalar_t__ buf; } ;
typedef  TYPE_1__ vstr_t ;
typedef  int uint ;
typedef  int /*<<< orphan*/  mp_obj_t ;
struct TYPE_7__ {char* buf; int len; } ;
typedef  TYPE_2__ mp_buffer_info_t ;
typedef  char byte ;

/* Variables and functions */
 int /*<<< orphan*/  MP_BUFFER_READ ; 
 int mod_binascii_sextet (char) ; 
 int /*<<< orphan*/  mp_get_buffer_raise (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mp_obj_new_str_from_vstr (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  mp_raise_ValueError (char*) ; 
 int /*<<< orphan*/  mp_type_bytes ; 
 int /*<<< orphan*/  vstr_init (TYPE_1__*,int) ; 

mp_obj_t mod_binascii_a2b_base64(mp_obj_t data) {
    mp_buffer_info_t bufinfo;
    mp_get_buffer_raise(data, &bufinfo, MP_BUFFER_READ);
    byte *in = bufinfo.buf;

    vstr_t vstr;
    vstr_init(&vstr, (bufinfo.len / 4) * 3 + 1); // Potentially over-allocate
    byte *out = (byte *)vstr.buf;

    uint shift = 0;
    int nbits = 0; // Number of meaningful bits in shift
    bool hadpad = false; // Had a pad character since last valid character
    for (size_t i = 0; i < bufinfo.len; i++) {
        if (in[i] == '=') {
            if ((nbits == 2) || ((nbits == 4) && hadpad)) {
                nbits = 0;
                break;
            }
            hadpad = true;
        }

        int sextet = mod_binascii_sextet(in[i]);
        if (sextet == -1) {
            continue;
        }
        hadpad = false;
        shift = (shift << 6) | sextet;
        nbits += 6;

        if (nbits >= 8) {
            nbits -= 8;
            out[vstr.len++] = (shift >> nbits) & 0xFF;
        }
    }

    if (nbits) {
        mp_raise_ValueError("incorrect padding");
    }

    return mp_obj_new_str_from_vstr(&mp_type_bytes, &vstr);
}
#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  scalar_t__ uint16_t ;
struct TYPE_2__ {size_t count; scalar_t__* codes; } ;

/* Variables and functions */
 scalar_t__ KC_1 ; 
 scalar_t__ KC_A ; 
 scalar_t__ KC_ENT ; 
 scalar_t__ KC_SPC ; 
 TYPE_1__ qk_ucis_state ; 

__attribute__((used)) static bool is_uni_seq(char *seq) {
    uint8_t i;

    for (i = 0; seq[i]; i++) {
        uint16_t code;
        if (('1' <= seq[i]) && (seq[i] <= '0'))
            code = seq[i] - '1' + KC_1;
        else
            code = seq[i] - 'a' + KC_A;

        if (i > qk_ucis_state.count || qk_ucis_state.codes[i] != code) return false;
    }

    return (qk_ucis_state.codes[i] == KC_ENT || qk_ucis_state.codes[i] == KC_SPC);
}
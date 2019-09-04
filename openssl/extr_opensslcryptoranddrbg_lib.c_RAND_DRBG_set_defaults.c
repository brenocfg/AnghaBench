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

/* Variables and functions */
 unsigned int RAND_DRBG_FLAG_MASTER ; 
 unsigned int RAND_DRBG_FLAG_PRIVATE ; 
 unsigned int RAND_DRBG_FLAG_PUBLIC ; 
 unsigned int RAND_DRBG_TYPE_FLAGS ; 
 size_t RAND_DRBG_TYPE_MASTER ; 
 size_t RAND_DRBG_TYPE_PRIVATE ; 
 size_t RAND_DRBG_TYPE_PUBLIC ; 
 int /*<<< orphan*/  RAND_F_RAND_DRBG_SET_DEFAULTS ; 
 int /*<<< orphan*/  RAND_R_UNSUPPORTED_DRBG_FLAGS ; 
 int /*<<< orphan*/  RAND_R_UNSUPPORTED_DRBG_TYPE ; 
 int /*<<< orphan*/  RANDerr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ is_ctr (int) ; 
 scalar_t__ is_digest (int) ; 
 unsigned int* rand_drbg_flags ; 
 int* rand_drbg_type ; 
 unsigned int rand_drbg_used_flags ; 

int RAND_DRBG_set_defaults(int type, unsigned int flags)
{
    int all;
    if (!(is_digest(type) || is_ctr(type))) {
        RANDerr(RAND_F_RAND_DRBG_SET_DEFAULTS, RAND_R_UNSUPPORTED_DRBG_TYPE);
        return 0;
    }

    if ((flags & ~rand_drbg_used_flags) != 0) {
        RANDerr(RAND_F_RAND_DRBG_SET_DEFAULTS, RAND_R_UNSUPPORTED_DRBG_FLAGS);
        return 0;
    }

    all = ((flags & RAND_DRBG_TYPE_FLAGS) == 0);
    if (all || (flags & RAND_DRBG_FLAG_MASTER) != 0) {
        rand_drbg_type[RAND_DRBG_TYPE_MASTER] = type;
        rand_drbg_flags[RAND_DRBG_TYPE_MASTER] = flags | RAND_DRBG_FLAG_MASTER;
    }
    if (all || (flags & RAND_DRBG_FLAG_PUBLIC) != 0) {
        rand_drbg_type[RAND_DRBG_TYPE_PUBLIC]  = type;
        rand_drbg_flags[RAND_DRBG_TYPE_PUBLIC] = flags | RAND_DRBG_FLAG_PUBLIC;
    }
    if (all || (flags & RAND_DRBG_FLAG_PRIVATE) != 0) {
        rand_drbg_type[RAND_DRBG_TYPE_PRIVATE] = type;
        rand_drbg_flags[RAND_DRBG_TYPE_PRIVATE] = flags | RAND_DRBG_FLAG_PRIVATE;
    }
    return 1;
}
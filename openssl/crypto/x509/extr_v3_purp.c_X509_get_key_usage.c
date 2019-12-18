#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int ex_flags; int /*<<< orphan*/  ex_kusage; } ;
typedef  TYPE_1__ X509 ;

/* Variables and functions */
 int EXFLAG_KUSAGE ; 
 int /*<<< orphan*/  UINT32_MAX ; 
 int /*<<< orphan*/  X509_check_purpose (TYPE_1__*,int,int) ; 

uint32_t X509_get_key_usage(X509 *x)
{
    /* Call for side-effect of computing hash and caching extensions */
    X509_check_purpose(x, -1, -1);
    if (x->ex_flags & EXFLAG_KUSAGE)
        return x->ex_kusage;
    return UINT32_MAX;
}
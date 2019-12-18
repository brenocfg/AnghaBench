#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  va_list ;
typedef  scalar_t__ uint32_t ;
struct TYPE_3__ {scalar_t__ error_lib; } ;
typedef  TYPE_1__ OSSL_PROVIDER ;

/* Variables and functions */
 scalar_t__ ERR_GET_LIB (scalar_t__) ; 
 int ERR_GET_REASON (scalar_t__) ; 
 int /*<<< orphan*/  ERR_vset_error (scalar_t__,int,char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void core_vset_error(const OSSL_PROVIDER *prov,
                            uint32_t reason, const char *fmt, va_list args)
{
    /*
     * If the uppermost 8 bits are non-zero, it's an OpenSSL library
     * error and will be treated as such.  Otherwise, it's a new style
     * provider error and will be treated as such.
     */
    if (ERR_GET_LIB(reason) != 0) {
        ERR_vset_error(ERR_GET_LIB(reason), ERR_GET_REASON(reason), fmt, args);
    } else {
        ERR_vset_error(prov->error_lib, (int)reason, fmt, args);
    }
}
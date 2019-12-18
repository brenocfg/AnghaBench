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
struct TYPE_4__ {int dwInfoStatus; int /*<<< orphan*/  dwErrorStatus; } ;
typedef  TYPE_1__ CERT_TRUST_STATUS ;

/* Variables and functions */

__attribute__((used)) static inline void CRYPT_CombineTrustStatus(CERT_TRUST_STATUS *chainStatus,
 const CERT_TRUST_STATUS *elementStatus)
{
    /* Any error that applies to an element also applies to a chain.. */
    chainStatus->dwErrorStatus |= elementStatus->dwErrorStatus;
    /* but the bottom nibble of an element's info status doesn't apply to the
     * chain.
     */
    chainStatus->dwInfoStatus |= (elementStatus->dwInfoStatus & 0xfffffff0);
}
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
typedef  int /*<<< orphan*/  PROV_CCM_HW ;

/* Variables and functions */
 int /*<<< orphan*/  const aes_ccm ; 

const PROV_CCM_HW *PROV_AES_HW_ccm(size_t keybits)
{
    return &aes_ccm;
}
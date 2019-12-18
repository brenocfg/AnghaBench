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
typedef  int /*<<< orphan*/  const PROV_CIPHER_HW ;

/* Variables and functions */
 int /*<<< orphan*/  rc4_hmac_md5_hw ; 

const PROV_CIPHER_HW *PROV_CIPHER_HW_rc4_hmac_md5(size_t keybits)
{
    return (PROV_CIPHER_HW *)&rc4_hmac_md5_hw;
}
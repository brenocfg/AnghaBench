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
typedef  int /*<<< orphan*/  PROV_CIPHER_HW_AES_SIV ;

/* Variables and functions */
 int /*<<< orphan*/  const aes_siv_hw ; 

const PROV_CIPHER_HW_AES_SIV *PROV_CIPHER_HW_aes_siv(size_t keybits)
{
    return &aes_siv_hw;
}
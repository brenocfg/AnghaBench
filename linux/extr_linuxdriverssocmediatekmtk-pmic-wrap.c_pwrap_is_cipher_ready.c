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
struct pmic_wrapper {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PWRAP_CIPHER_RDY ; 
 int pwrap_readl (struct pmic_wrapper*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool pwrap_is_cipher_ready(struct pmic_wrapper *wrp)
{
	return pwrap_readl(wrp, PWRAP_CIPHER_RDY) & 1;
}
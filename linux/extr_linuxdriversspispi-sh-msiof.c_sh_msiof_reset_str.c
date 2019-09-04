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
struct sh_msiof_spi_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  STR ; 
 int STR_RDREQ ; 
 int STR_TDREQ ; 
 int sh_msiof_read (struct sh_msiof_spi_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sh_msiof_write (struct sh_msiof_spi_priv*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void sh_msiof_reset_str(struct sh_msiof_spi_priv *p)
{
	sh_msiof_write(p, STR,
		       sh_msiof_read(p, STR) & ~(STR_TDREQ | STR_RDREQ));
}
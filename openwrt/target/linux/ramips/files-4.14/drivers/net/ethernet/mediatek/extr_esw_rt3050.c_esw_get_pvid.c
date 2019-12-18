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
struct rt305x_esw {int dummy; } ;

/* Variables and functions */
 unsigned int RT305X_ESW_PVIDC_PVID_M ; 
 unsigned int RT305X_ESW_PVIDC_PVID_S ; 
 int /*<<< orphan*/  RT305X_ESW_REG_PVIDC (unsigned int) ; 
 unsigned int esw_r32 (struct rt305x_esw*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static unsigned esw_get_pvid(struct rt305x_esw *esw, unsigned port)
{
	unsigned s, val;

	s = RT305X_ESW_PVIDC_PVID_S * (port % 2);
	val = esw_r32(esw, RT305X_ESW_REG_PVIDC(port / 2));
	return (val >> s) & RT305X_ESW_PVIDC_PVID_M;
}
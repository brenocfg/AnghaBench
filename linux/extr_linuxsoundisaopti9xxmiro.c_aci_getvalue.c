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
struct snd_miro_aci {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACI_STATUS ; 
 int snd_aci_cmd (struct snd_miro_aci*,int /*<<< orphan*/ ,unsigned char,int) ; 

__attribute__((used)) static int aci_getvalue(struct snd_miro_aci *aci, unsigned char index)
{
	return snd_aci_cmd(aci, ACI_STATUS, index, -1);
}
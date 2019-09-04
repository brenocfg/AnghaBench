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
typedef  int u8 ;
struct AdapterCtlBlk {int dummy; } ;

/* Variables and functions */
 int AUTOTERM ; 
 int CON50 ; 
 int CON5068 ; 
 int CON68 ; 
 int DC395x_read8 (struct AdapterCtlBlk*,int /*<<< orphan*/ ) ; 
 int DIS_TERM ; 
 int EXT68HIGH ; 
 int INT68HIGH ; 
 int /*<<< orphan*/  KERN_INFO ; 
 int LOW8TERM ; 
 int /*<<< orphan*/  TRM_S1040_GEN_CONTROL ; 
 int /*<<< orphan*/  TRM_S1040_GEN_STATUS ; 
 int UP8TERM ; 
 int WIDESCSI ; 
 int /*<<< orphan*/  dprintkl (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  printk (char*,...) ; 

__attribute__((used)) static void adapter_print_config(struct AdapterCtlBlk *acb)
{
	u8 bval;

	bval = DC395x_read8(acb, TRM_S1040_GEN_STATUS);
	dprintkl(KERN_INFO, "%sConnectors: ",
		((bval & WIDESCSI) ? "(Wide) " : ""));
	if (!(bval & CON5068))
		printk("ext%s ", !(bval & EXT68HIGH) ? "68" : "50");
	if (!(bval & CON68))
		printk("int68%s ", !(bval & INT68HIGH) ? "" : "(50)");
	if (!(bval & CON50))
		printk("int50 ");
	if ((bval & (CON5068 | CON50 | CON68)) ==
	    0 /*(CON5068 | CON50 | CON68) */ )
		printk(" Oops! (All 3?) ");
	bval = DC395x_read8(acb, TRM_S1040_GEN_CONTROL);
	printk(" Termination: ");
	if (bval & DIS_TERM)
		printk("Disabled\n");
	else {
		if (bval & AUTOTERM)
			printk("Auto ");
		if (bval & LOW8TERM)
			printk("Low ");
		if (bval & UP8TERM)
			printk("High ");
		printk("\n");
	}
}
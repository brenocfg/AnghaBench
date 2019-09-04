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
struct sym_hcb {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  HS_UNEXPECTED ; 
 int /*<<< orphan*/  printf (char*,char*) ; 
 char* sym_name (struct sym_hcb*) ; 
 int /*<<< orphan*/  sym_recover_scsi_int (struct sym_hcb*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sym_int_udc (struct sym_hcb *np)
{
	printf ("%s: unexpected disconnect\n", sym_name(np));
	sym_recover_scsi_int(np, HS_UNEXPECTED);
}
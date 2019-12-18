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
struct LRMI_regs {int eax; int edx; int ebx; int ecx; } ;
typedef  int /*<<< orphan*/  r ;

/* Variables and functions */
 int /*<<< orphan*/  LRMI_init () ; 
 int LRMI_int (int,struct LRMI_regs*) ; 
 int /*<<< orphan*/  memset (struct LRMI_regs*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

int main (void)
{
	struct LRMI_regs	r;
	int			retval;

	if (!LRMI_init())
		return 0;

	memset(&r, 0, sizeof(r));

	r.eax = 0x0000E980;
	r.edx = 0x47534943;

	retval = LRMI_int(0x15, &r);

	if (!retval) {
		printf("Failed!\n");
		return 0;
	}
	if (r.eax == 0x47534943) {
		printf("BIOS supports GSIC call:\n");
		printf("\tsignature: %c%c%c%c\n",
		       (r.eax >> 24) & 0xff,
		       (r.eax >> 16) & 0xff,
		       (r.eax >> 8) & 0xff,
		       (r.eax) & 0xff);
		printf("\tcommand port = 0x%.4x\n",
		       r.ebx & 0xffff);
		printf("\tcommand =      0x%.4x\n",
		       (r.ebx >> 16) & 0xffff);
		printf("\tevent port =   0x%.8x\n", r.ecx);
		printf("\tflags =        0x%.8x\n", r.edx);
		if (((r.ebx >> 16) & 0xffff) != 0x82) {
			printf("non-default command value. If speedstep-smi "
			       "doesn't work out of the box,\nyou may want to "
			       "try out the default value by passing "
			       "smi_cmd=0x82 to the module\n ON YOUR OWN "
			       "RISK.\n");
		}
		if ((r.ebx & 0xffff) != 0xb2) {
			printf("non-default command port. If speedstep-smi "
			       "doesn't work out of the box,\nyou may want to "
			       "try out the default value by passing "
			       "smi_port=0x82 to the module\n ON YOUR OWN "
			       "RISK.\n");
		}
	} else {
		printf("BIOS DOES NOT support GSIC call.  Dumping registers anyway:\n");
		printf("eax = 0x%.8x\n", r.eax);
		printf("ebx = 0x%.8x\n", r.ebx);
		printf("ecx = 0x%.8x\n", r.ecx);
		printf("edx = 0x%.8x\n", r.edx);
		printf("Note also that some BIOS do not support the initial "
		       "GSIC call, but the newer\nspeedstep-smi driver may "
		       "work.\nFor this, you need to pass some arguments to "
		       "the speedstep-smi driver:\n");
		printf("\tsmi_cmd=0x?? smi_port=0x?? smi_sig=1\n");
		printf("\nUnfortunately, you have to know what exactly are "
		       "smi_cmd and smi_port, and this\nis system "
		       "dependant.\n");
	}
	return 1;
}
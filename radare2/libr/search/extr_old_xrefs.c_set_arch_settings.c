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

/* Variables and functions */
#define  ARCH_ARM 131 
#define  ARCH_NULL 130 
#define  ARCH_PPC 129 
#define  ARCH_X86 128 
 int arch ; 
 int delta ; 
 int endian ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int gamme ; 
 int* ma ; 
 int /*<<< orphan*/  memcmp (int*,char*,int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  quite ; 
 int size ; 
 int /*<<< orphan*/  stderr ; 

int set_arch_settings()
{
	switch(arch) {
	case ARCH_PPC:
		gamme  = 1;
		delta  = 1;
		size   = 3;
		break;
	case ARCH_ARM:
		gamme  = -1;
		delta  = 1;
		size   = 3;
		break;
	case ARCH_X86:
		gamme  = 1;
		delta  = 0; //-5;
		size   = 4;
		break;
	case ARCH_NULL:
		/* autodetect architecture */
		// ELF
		if (!memcmp(ma, "\x7f\x45\x4c\x46", 4)) {
			short ar = (ma[0x12]<<8) + ma[0x13];
			switch(ar) {
			case 0x0300:
				if (endian==-1)
					endian = 1;
				if (!quite)
					printf("# -a x86\n");
				arch = ARCH_X86;
				endian = 1;
				return 1;
			case 0x0014:
				if (endian==-1)
					endian = 0;
				if (!quite)
				printf("# -a ppc\n");
				arch = ARCH_PPC;
				return 1;
			case 0x2800:
				if (endian==-1)
					endian = 1;
				if (!quite)
				printf("# -a arm\n");
				arch = ARCH_ARM;
				return 1;
			default:
				printf("Unsupported architecture '%04x'.\n", ar);
				exit(1);
			}
		} else
		// MZ
		if (!memcmp(ma, "\x4d\x5a",2)) {
			unsigned short off = ma[0x3c];
			if (!memcmp(ma+off, "PE\x00\x00",4)) {
				unsigned short ar = (ma[off+4]<<8)+ma[off+5];
				switch(ar) {
				case 0x4c01: // x86
					if (endian==-1)
						endian = 1;
					printf("# -a x86\n");
					arch = ARCH_X86;
					endian = 1;
					return 1;
				case 0xc001: // arm
					if (endian==-1)
						endian = 1;
					printf("# -a arm\n");
					arch = ARCH_ARM;
					endian = 1;
					return 1;
				default:
					fprintf(stderr, "Unknown architecture.\n");
					break;
				}
			}
		} else {
			fprintf(stderr, "Plz. gimmie an architecture. (xrefs -a [arch])\n");
			exit(1);
		}
	}

	return 0;
}
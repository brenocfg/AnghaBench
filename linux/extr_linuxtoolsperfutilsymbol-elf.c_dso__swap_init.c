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
struct dso {void* needs_swap; } ;

/* Variables and functions */
 void* DSO_SWAP__NO ; 
 void* DSO_SWAP__YES ; 
 int EINVAL ; 
#define  ELFDATA2LSB 129 
#define  ELFDATA2MSB 128 
 int /*<<< orphan*/  pr_err (char*,unsigned char) ; 

__attribute__((used)) static int dso__swap_init(struct dso *dso, unsigned char eidata)
{
	static unsigned int const endian = 1;

	dso->needs_swap = DSO_SWAP__NO;

	switch (eidata) {
	case ELFDATA2LSB:
		/* We are big endian, DSO is little endian. */
		if (*(unsigned char const *)&endian != 1)
			dso->needs_swap = DSO_SWAP__YES;
		break;

	case ELFDATA2MSB:
		/* We are little endian, DSO is big endian. */
		if (*(unsigned char const *)&endian != 0)
			dso->needs_swap = DSO_SWAP__YES;
		break;

	default:
		pr_err("unrecognized DSO data encoding %d\n", eidata);
		return -EINVAL;
	}

	return 0;
}
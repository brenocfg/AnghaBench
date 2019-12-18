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
struct pci_test {int barnum; int size; char* device; int legacyirq; int msinum; int msixnum; int irqtype; int set_irqtype; int get_irqtype; int read; int write; int copy; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int EOF ; 
 void* atoi (char*) ; 
 struct pci_test* calloc (int,int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int getopt (int,char**,char*) ; 
 char* optarg ; 
 int /*<<< orphan*/  perror (char*) ; 
 int run_test (struct pci_test*) ; 
 int /*<<< orphan*/  stderr ; 
 int strtoul (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int main(int argc, char **argv)
{
	int c;
	struct pci_test *test;

	test = calloc(1, sizeof(*test));
	if (!test) {
		perror("Fail to allocate memory for pci_test\n");
		return -ENOMEM;
	}

	/* since '0' is a valid BAR number, initialize it to -1 */
	test->barnum = -1;

	/* set default size as 100KB */
	test->size = 0x19000;

	/* set default endpoint device */
	test->device = "/dev/pci-endpoint-test.0";

	while ((c = getopt(argc, argv, "D:b:m:x:i:Ilhrwcs:")) != EOF)
	switch (c) {
	case 'D':
		test->device = optarg;
		continue;
	case 'b':
		test->barnum = atoi(optarg);
		if (test->barnum < 0 || test->barnum > 5)
			goto usage;
		continue;
	case 'l':
		test->legacyirq = true;
		continue;
	case 'm':
		test->msinum = atoi(optarg);
		if (test->msinum < 1 || test->msinum > 32)
			goto usage;
		continue;
	case 'x':
		test->msixnum = atoi(optarg);
		if (test->msixnum < 1 || test->msixnum > 2048)
			goto usage;
		continue;
	case 'i':
		test->irqtype = atoi(optarg);
		if (test->irqtype < 0 || test->irqtype > 2)
			goto usage;
		test->set_irqtype = true;
		continue;
	case 'I':
		test->get_irqtype = true;
		continue;
	case 'r':
		test->read = true;
		continue;
	case 'w':
		test->write = true;
		continue;
	case 'c':
		test->copy = true;
		continue;
	case 's':
		test->size = strtoul(optarg, NULL, 0);
		continue;
	case 'h':
	default:
usage:
		fprintf(stderr,
			"usage: %s [options]\n"
			"Options:\n"
			"\t-D <dev>		PCI endpoint test device {default: /dev/pci-endpoint-test.0}\n"
			"\t-b <bar num>		BAR test (bar number between 0..5)\n"
			"\t-m <msi num>		MSI test (msi number between 1..32)\n"
			"\t-x <msix num>	\tMSI-X test (msix number between 1..2048)\n"
			"\t-i <irq type>	\tSet IRQ type (0 - Legacy, 1 - MSI, 2 - MSI-X)\n"
			"\t-I			Get current IRQ type configured\n"
			"\t-l			Legacy IRQ test\n"
			"\t-r			Read buffer test\n"
			"\t-w			Write buffer test\n"
			"\t-c			Copy buffer test\n"
			"\t-s <size>		Size of buffer {default: 100KB}\n"
			"\t-h			Print this help message\n",
			argv[0]);
		return -EINVAL;
	}

	return run_test(test);
}
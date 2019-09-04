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
struct device {int dummy; } ;
struct rproc {char* firmware; struct device dev; } ;
struct firmware {int size; scalar_t__ data; } ;
struct elf32_shdr {int dummy; } ;
struct elf32_hdr {char* e_ident; scalar_t__ e_shoff; scalar_t__ e_phnum; scalar_t__ e_phoff; } ;

/* Variables and functions */
 int EINVAL ; 
 size_t EI_CLASS ; 
 size_t EI_DATA ; 
 char ELFCLASS32 ; 
 char ELFDATA2MSB ; 
 int /*<<< orphan*/  ELFMAG ; 
 int /*<<< orphan*/  SELFMAG ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,...) ; 
 scalar_t__ memcmp (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int rproc_elf_sanity_check(struct rproc *rproc, const struct firmware *fw)
{
	const char *name = rproc->firmware;
	struct device *dev = &rproc->dev;
	struct elf32_hdr *ehdr;
	char class;

	if (!fw) {
		dev_err(dev, "failed to load %s\n", name);
		return -EINVAL;
	}

	if (fw->size < sizeof(struct elf32_hdr)) {
		dev_err(dev, "Image is too small\n");
		return -EINVAL;
	}

	ehdr = (struct elf32_hdr *)fw->data;

	/* We only support ELF32 at this point */
	class = ehdr->e_ident[EI_CLASS];
	if (class != ELFCLASS32) {
		dev_err(dev, "Unsupported class: %d\n", class);
		return -EINVAL;
	}

	/* We assume the firmware has the same endianness as the host */
# ifdef __LITTLE_ENDIAN
	if (ehdr->e_ident[EI_DATA] != ELFDATA2LSB) {
# else /* BIG ENDIAN */
	if (ehdr->e_ident[EI_DATA] != ELFDATA2MSB) {
# endif
		dev_err(dev, "Unsupported firmware endianness\n");
		return -EINVAL;
	}

	if (fw->size < ehdr->e_shoff + sizeof(struct elf32_shdr)) {
		dev_err(dev, "Image is too small\n");
		return -EINVAL;
	}

	if (memcmp(ehdr->e_ident, ELFMAG, SELFMAG)) {
		dev_err(dev, "Image is corrupted (bad magic)\n");
		return -EINVAL;
	}

	if (ehdr->e_phnum == 0) {
		dev_err(dev, "No loadable segments\n");
		return -EINVAL;
	}

	if (ehdr->e_phoff > fw->size) {
		dev_err(dev, "Firmware size is too small\n");
		return -EINVAL;
	}

	return 0;
}
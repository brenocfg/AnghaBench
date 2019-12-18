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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  magic ;

/* Variables and functions */
#define  MTD_IMAGE_FORMAT_SEAMA 131 
#define  MTD_IMAGE_FORMAT_TRX 130 
#define  MTD_IMAGE_FORMAT_WRG 129 
#define  MTD_IMAGE_FORMAT_WRGG03 128 
 scalar_t__ SEAMA_MAGIC ; 
 scalar_t__ TRX_MAGIC ; 
 scalar_t__ WRGG03_MAGIC ; 
 scalar_t__ WRG_MAGIC ; 
 scalar_t__ be32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ buf ; 
 int buflen ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 int imageformat ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 int read (int,scalar_t__,int) ; 
 int /*<<< orphan*/  stdout ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int trx_check (int,char const*,scalar_t__,int*) ; 

__attribute__((used)) static int
image_check(int imagefd, const char *mtd)
{
	uint32_t magic;
	int ret = 1;
	int bufread;

	while (buflen < sizeof(magic)) {
		bufread = read(imagefd, buf + buflen, sizeof(magic) - buflen);
		if (bufread < 1)
			break;

		buflen += bufread;
	}

	if (buflen < sizeof(magic)) {
		fprintf(stdout, "Could not get image magic\n");
		return 0;
	}

	magic = ((uint32_t *)buf)[0];

	if (be32_to_cpu(magic) == TRX_MAGIC)
		imageformat = MTD_IMAGE_FORMAT_TRX;
	else if (be32_to_cpu(magic) == SEAMA_MAGIC)
		imageformat = MTD_IMAGE_FORMAT_SEAMA;
	else if (le32_to_cpu(magic) == WRG_MAGIC)
		imageformat = MTD_IMAGE_FORMAT_WRG;
	else if (le32_to_cpu(magic) == WRGG03_MAGIC)
		imageformat = MTD_IMAGE_FORMAT_WRGG03;

	switch (imageformat) {
	case MTD_IMAGE_FORMAT_TRX:
		if (trx_check)
			ret = trx_check(imagefd, mtd, buf, &buflen);
		break;
	case MTD_IMAGE_FORMAT_SEAMA:
	case MTD_IMAGE_FORMAT_WRG:
	case MTD_IMAGE_FORMAT_WRGG03:
		break;
	default:
#ifdef target_brcm
		if (!strcmp(mtd, "firmware"))
			ret = 0;
#endif
		break;
	}

	return ret;
}
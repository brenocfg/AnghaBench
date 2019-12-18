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
struct file_info {int file_size; int /*<<< orphan*/  file_name; scalar_t__ file_data; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  DBG (char*,...) ; 
 int /*<<< orphan*/  ERR (char*,...) ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int footer_sz ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 int fread (scalar_t__,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,long,int /*<<< orphan*/ ) ; 
 int ftell (int /*<<< orphan*/ *) ; 
 int header_sz ; 
 scalar_t__ is_header ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rewind (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int copyToOutputBuf(struct file_info* finfo) {
	FILE* fp = NULL;

	int file_sz = 0;
	int extra_sz;
	int hdr_pos;
	int img_pos;

	if (!finfo || !finfo->file_name) {
		ERR("Invalid pointer provided!\n");
		return -1;
	}

	DBG("Opening file: %s\n", finfo->file_name);

	if (!(fp = fopen(finfo->file_name, "rb"))) {
		ERR("Error opening file: %s\n", finfo->file_name);
		return -1;
	}

	/* Get filesize */
	rewind(fp);
	fseek(fp, 0L, SEEK_END);
	file_sz = ftell(fp);
	rewind(fp);

	if (file_sz < 1) {
		ERR("Error getting filesize: %s\n", finfo->file_name);
		fclose(fp);
		return -1;
	}

	if (is_header) {
		extra_sz = header_sz;
		hdr_pos = 0;
		img_pos = header_sz;
	} else {
		extra_sz = footer_sz;
		hdr_pos = file_sz;
		img_pos = 0;
	}

	DBG("Filesize: %i\n", file_sz);
	finfo->file_size = file_sz + extra_sz;

	if (!(finfo->file_data = malloc(finfo->file_size))) {
		ERR("Out of memory!\n");
		fclose(fp);
		return -1;
	}

	/* init header/footer bytes */
	memset(finfo->file_data + hdr_pos, 0, extra_sz);

	/* read file and take care of leading header if exists */
	if (fread(finfo->file_data + img_pos, 1, file_sz, fp) != file_sz) {
		ERR("Error reading file %s\n", finfo->file_name);
		fclose(fp);
		return -1;
	}

	DBG("File: read successful\n");
	fclose(fp);

	return hdr_pos;
}
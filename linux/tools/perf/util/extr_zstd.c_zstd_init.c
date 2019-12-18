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
struct zstd_data {int /*<<< orphan*/ * cstream; int /*<<< orphan*/ * dstream; } ;

/* Variables and functions */
 int /*<<< orphan*/ * ZSTD_createCStream () ; 
 int /*<<< orphan*/ * ZSTD_createDStream () ; 
 int /*<<< orphan*/  ZSTD_getErrorName (size_t) ; 
 size_t ZSTD_initCStream (int /*<<< orphan*/ *,int) ; 
 size_t ZSTD_initDStream (int /*<<< orphan*/ *) ; 
 scalar_t__ ZSTD_isError (size_t) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 

int zstd_init(struct zstd_data *data, int level)
{
	size_t ret;

	data->dstream = ZSTD_createDStream();
	if (data->dstream == NULL) {
		pr_err("Couldn't create decompression stream.\n");
		return -1;
	}

	ret = ZSTD_initDStream(data->dstream);
	if (ZSTD_isError(ret)) {
		pr_err("Failed to initialize decompression stream: %s\n", ZSTD_getErrorName(ret));
		return -1;
	}

	if (!level)
		return 0;

	data->cstream = ZSTD_createCStream();
	if (data->cstream == NULL) {
		pr_err("Couldn't create compression stream.\n");
		return -1;
	}

	ret = ZSTD_initCStream(data->cstream, level);
	if (ZSTD_isError(ret)) {
		pr_err("Failed to initialize compression stream: %s\n", ZSTD_getErrorName(ret));
		return -1;
	}

	return 0;
}
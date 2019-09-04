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
struct firmware {int dummy; } ;
struct ath10k {int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  filename ;

/* Variables and functions */
 int /*<<< orphan*/  ATH10K_DBG_BOOT ; 
 int ENOENT ; 
 struct firmware const* ERR_PTR (int) ; 
 int /*<<< orphan*/  ath10k_dbg (struct ath10k*,int /*<<< orphan*/ ,char*,char*,int) ; 
 int firmware_request_nowarn (struct firmware const**,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char const*) ; 

__attribute__((used)) static const struct firmware *ath10k_fetch_fw_file(struct ath10k *ar,
						   const char *dir,
						   const char *file)
{
	char filename[100];
	const struct firmware *fw;
	int ret;

	if (file == NULL)
		return ERR_PTR(-ENOENT);

	if (dir == NULL)
		dir = ".";

	snprintf(filename, sizeof(filename), "%s/%s", dir, file);
	ret = firmware_request_nowarn(&fw, filename, ar->dev);
	ath10k_dbg(ar, ATH10K_DBG_BOOT, "boot fw request '%s': %d\n",
		   filename, ret);

	if (ret)
		return ERR_PTR(ret);

	return fw;
}
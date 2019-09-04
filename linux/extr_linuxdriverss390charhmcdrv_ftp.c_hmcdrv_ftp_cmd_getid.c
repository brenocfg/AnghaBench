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
typedef  int u16 ;
typedef  enum hmcdrv_ftp_cmdid { ____Placeholder_hmcdrv_ftp_cmdid } hmcdrv_ftp_cmdid ;

/* Variables and functions */
 int ARRAY_SIZE (struct hmcdrv_ftp_cmd_desc const*) ; 
#define  HMCDRV_FTP_APPEND 133 
#define  HMCDRV_FTP_DELETE 132 
#define  HMCDRV_FTP_DIR 131 
#define  HMCDRV_FTP_GET 130 
#define  HMCDRV_FTP_NLIST 129 
 int HMCDRV_FTP_NOOP ; 
#define  HMCDRV_FTP_PUT 128 
 int crc16 (int,int,int) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 scalar_t__ strncmp (char*,int,int) ; 

__attribute__((used)) static enum hmcdrv_ftp_cmdid hmcdrv_ftp_cmd_getid(const char *cmd, int len)
{
	/* HMC FTP command descriptor */
	struct hmcdrv_ftp_cmd_desc {
		const char *str;	   /* command string */
		enum hmcdrv_ftp_cmdid cmd; /* associated command as enum */
	};

	/* Description of all HMC drive FTP commands
	 *
	 * Notes:
	 * 1. Array size should be a prime number.
	 * 2. Do not change the order of commands in table (because the
	 *    index is determined by CRC % ARRAY_SIZE).
	 * 3. Original command 'nlist' was renamed, else the CRC would
	 *    collide with 'append' (see point 2).
	 */
	static const struct hmcdrv_ftp_cmd_desc ftpcmds[7] = {

		{.str = "get", /* [0] get (CRC = 0x68eb) */
		 .cmd = HMCDRV_FTP_GET},
		{.str = "dir", /* [1] dir (CRC = 0x6a9e) */
		 .cmd = HMCDRV_FTP_DIR},
		{.str = "delete", /* [2] delete (CRC = 0x53ae) */
		 .cmd = HMCDRV_FTP_DELETE},
		{.str = "nls", /* [3] nls (CRC = 0xf87c) */
		 .cmd = HMCDRV_FTP_NLIST},
		{.str = "put", /* [4] put (CRC = 0xac56) */
		 .cmd = HMCDRV_FTP_PUT},
		{.str = "append", /* [5] append (CRC = 0xf56e) */
		 .cmd = HMCDRV_FTP_APPEND},
		{.str = NULL} /* [6] unused */
	};

	const struct hmcdrv_ftp_cmd_desc *pdesc;

	u16 crc = 0xffffU;

	if (len == 0)
		return HMCDRV_FTP_NOOP; /* error indiactor */

	crc = crc16(crc, cmd, len);
	pdesc = ftpcmds + (crc % ARRAY_SIZE(ftpcmds));
	pr_debug("FTP command '%s' has CRC 0x%04x, at table pos. %lu\n",
		 cmd, crc, (crc % ARRAY_SIZE(ftpcmds)));

	if (!pdesc->str || strncmp(pdesc->str, cmd, len))
		return HMCDRV_FTP_NOOP;

	pr_debug("FTP command '%s' found, with ID %d\n",
		 pdesc->str, pdesc->cmd);

	return pdesc->cmd;
}
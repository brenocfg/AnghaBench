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
typedef  int /*<<< orphan*/  uint8 ;
struct usr_header {scalar_t__ len; int /*<<< orphan*/  crc32; scalar_t__* reserved; int /*<<< orphan*/  hardware_revision; int /*<<< orphan*/  compatibility_id; int /*<<< orphan*/  version; int /*<<< orphan*/  magic; } ;
typedef  int /*<<< orphan*/  hdr ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  CHUNK ; 
 int /*<<< orphan*/  COMPAT_ID ; 
 int /*<<< orphan*/  CRC32_INIT ; 
 int /*<<< orphan*/  EPI_VERSION ; 
 int /*<<< orphan*/  HARDWARE_REV ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int /*<<< orphan*/  TRX_MAGIC ; 
 int /*<<< orphan*/  USR_MAGIC ; 
 struct usr_header buf ; 
 int /*<<< orphan*/  crc32 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t) ; 
 scalar_t__ ferror (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*) ; 
 size_t fread (struct usr_header,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fseek (int /*<<< orphan*/ *,long,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fwrite (struct usr_header*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (struct usr_header,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static	int	trx2usr(FILE* trx, FILE* usr)
{
	struct usr_header	hdr;
	size_t			n;

	hdr.magic		= USR_MAGIC;
	hdr.len			= 0;
	hdr.crc32		= CRC32_INIT;
	hdr.version		= EPI_VERSION;
	hdr.compatibility_id	= COMPAT_ID;
	hdr.hardware_revision	= HARDWARE_REV;
	hdr.reserved[0]		= 0;
	hdr.reserved[1]		= 0;
	fwrite(& hdr, sizeof(hdr), 1, usr);
	while ((n = fread(buf, 1, CHUNK, trx)))
	{
		if (hdr.len == 0 && strncmp(buf, TRX_MAGIC, strlen(TRX_MAGIC)) != 0)
		{
			break;
		}
		fwrite(& buf, 1, n, usr);
		hdr.len += n;
		hdr.crc32 = crc32( hdr.crc32, (uint8 *) & buf, n);
	}
	fseek(usr, 0L, SEEK_SET);
	fwrite(& hdr, sizeof(hdr), 1, usr);
	if (n != 0)
	{
		fprintf(stderr, "Input is not a TRX file\n");
		return 1;
	}
	if (hdr.len == 0)
	{
		fprintf(stderr, "Empty input\n");
		return 1;
	}
	if (ferror(trx))
	{
		fprintf(stderr, "Read error\n");
		return 1;
	}
	if (ferror(usr))
	{
		fprintf(stderr, "Write error\n");
		return 1;
	}
	return 0;
}
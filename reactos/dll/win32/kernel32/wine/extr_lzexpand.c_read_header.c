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
struct lzfileheader {char* magic; char compressiontype; char lastchar; char reallength; } ;
typedef  int INT ;
typedef  int /*<<< orphan*/  HFILE ;
typedef  int /*<<< orphan*/  BYTE ;

/* Variables and functions */
 int LZERROR_BADINHANDLE ; 
 int LZERROR_UNKNOWNALG ; 
 int /*<<< orphan*/  LZMagic ; 
 int LZ_HEADER_LEN ; 
 int LZ_MAGIC_LEN ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int _llseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int _lread (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 scalar_t__ memcmp (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static INT read_header(HFILE fd,struct lzfileheader *head)
{
	BYTE	buf[LZ_HEADER_LEN];

	if (_llseek(fd,0,SEEK_SET)==-1)
		return LZERROR_BADINHANDLE;

	/* We can't directly read the lzfileheader struct due to
	 * structure element alignment
	 */
	if (_lread(fd,buf,LZ_HEADER_LEN)<LZ_HEADER_LEN)
		return 0;
	memcpy(head->magic,buf,LZ_MAGIC_LEN);
	memcpy(&(head->compressiontype),buf+LZ_MAGIC_LEN,1);
	memcpy(&(head->lastchar),buf+LZ_MAGIC_LEN+1,1);

	/* FIXME: consider endianness on non-intel architectures */
	memcpy(&(head->reallength),buf+LZ_MAGIC_LEN+2,4);

	if (memcmp(head->magic,LZMagic,LZ_MAGIC_LEN))
		return 0;
	if (head->compressiontype!='A')
		return LZERROR_UNKNOWNALG;
	return 1;
}
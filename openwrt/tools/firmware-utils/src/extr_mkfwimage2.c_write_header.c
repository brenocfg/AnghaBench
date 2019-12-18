#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_int32_t ;
struct TYPE_4__ {long pad; int /*<<< orphan*/  crc; int /*<<< orphan*/  version; int /*<<< orphan*/  magic; } ;
typedef  TYPE_1__ header_t ;
struct TYPE_5__ {int /*<<< orphan*/  magic; } ;

/* Variables and functions */
 int /*<<< orphan*/  MAGIC_LENGTH ; 
 int /*<<< orphan*/  crc32 (long,unsigned char*,int) ; 
 int /*<<< orphan*/  htonl (int /*<<< orphan*/ ) ; 
 TYPE_3__ im ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  strncpy (int /*<<< orphan*/ ,char const*,int) ; 

__attribute__((used)) static void write_header(void* mem, const char* version)
{
	header_t* header = mem;
	memset(header, 0, sizeof(header_t));

	memcpy(header->magic, im.magic, MAGIC_LENGTH);
	strncpy(header->version, version, sizeof(header->version));
	header->crc = htonl(crc32(0L, (unsigned char *)header,
				sizeof(header_t) - 2 * sizeof(u_int32_t)));
	header->pad = 0L;
}
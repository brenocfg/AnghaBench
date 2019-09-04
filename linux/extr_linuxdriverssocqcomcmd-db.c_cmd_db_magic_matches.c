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
typedef  int /*<<< orphan*/  u8 ;
struct cmd_db_header {int /*<<< orphan*/ * magic; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  CMD_DB_MAGIC ; 
 scalar_t__ memcmp (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool cmd_db_magic_matches(const struct cmd_db_header *header)
{
	const u8 *magic = header->magic;

	return memcmp(magic, CMD_DB_MAGIC, ARRAY_SIZE(CMD_DB_MAGIC)) == 0;
}
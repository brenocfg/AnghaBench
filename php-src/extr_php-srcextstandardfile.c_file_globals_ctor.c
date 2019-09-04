#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  def_chunk_size; } ;
typedef  TYPE_1__ php_file_globals ;

/* Variables and functions */
 int /*<<< orphan*/  PHP_SOCK_CHUNK_SIZE ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void file_globals_ctor(php_file_globals *file_globals_p)
{
	memset(file_globals_p, 0, sizeof(php_file_globals));
	file_globals_p->def_chunk_size = PHP_SOCK_CHUNK_SIZE;
}
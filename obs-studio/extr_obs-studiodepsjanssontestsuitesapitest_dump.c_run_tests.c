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

/* Variables and functions */
 int /*<<< orphan*/  circular_references () ; 
 int /*<<< orphan*/  dump_file () ; 
 int /*<<< orphan*/  encode_nul_byte () ; 
 int /*<<< orphan*/  encode_null () ; 
 int /*<<< orphan*/  encode_other_than_array_or_object () ; 
 int /*<<< orphan*/  encode_twice () ; 
 int /*<<< orphan*/  escape_slashes () ; 

__attribute__((used)) static void run_tests()
{
    encode_null();
    encode_twice();
    circular_references();
    encode_other_than_array_or_object();
    escape_slashes();
    encode_nul_byte();
    dump_file();
}
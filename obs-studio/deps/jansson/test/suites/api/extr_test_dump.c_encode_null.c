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
 int /*<<< orphan*/  JSON_ENCODE_ANY ; 
 int /*<<< orphan*/  encode_null_callback ; 
 int /*<<< orphan*/  fail (char*) ; 
 int json_dump_callback (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int json_dumpf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * json_dumps (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void encode_null()
{
    if(json_dumps(NULL, JSON_ENCODE_ANY) != NULL)
        fail("json_dumps didn't fail for NULL");

    if(json_dumpf(NULL, stderr, JSON_ENCODE_ANY) != -1)
        fail("json_dumpf didn't fail for NULL");

    /* Don't test json_dump_file to avoid creating a file */

    if(json_dump_callback(NULL, encode_null_callback, NULL, JSON_ENCODE_ANY) != -1)
        fail("json_dump_callback didn't fail for NULL");
}
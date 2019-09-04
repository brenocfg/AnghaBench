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
typedef  int /*<<< orphan*/  json_error_t ;

/* Variables and functions */
 int /*<<< orphan*/  JSON_REJECT_DUPLICATES ; 
 int /*<<< orphan*/  check_error (char*,char*,int,int,int) ; 
 int /*<<< orphan*/  fail (char*) ; 
 scalar_t__ json_loads (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void reject_duplicates()
{
    json_error_t error;

    if(json_loads("{\"foo\": 1, \"foo\": 2}", JSON_REJECT_DUPLICATES, &error))
        fail("json_loads did not detect a duplicate key");
    check_error("duplicate object key near '\"foo\"'", "<string>", 1, 16, 16);
}
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
 int /*<<< orphan*/  allow_nul () ; 
 int /*<<< orphan*/  decode_any () ; 
 int /*<<< orphan*/  decode_int_as_real () ; 
 int /*<<< orphan*/  disable_eof_check () ; 
 int /*<<< orphan*/  file_not_found () ; 
 int /*<<< orphan*/  load_wrong_args () ; 
 int /*<<< orphan*/  position () ; 
 int /*<<< orphan*/  reject_duplicates () ; 
 int /*<<< orphan*/  very_long_file_name () ; 

__attribute__((used)) static void run_tests()
{
    file_not_found();
    very_long_file_name();
    reject_duplicates();
    disable_eof_check();
    decode_any();
    decode_int_as_real();
    allow_nul();
    load_wrong_args();
    position();
}
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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  TidyDoc ;

/* Variables and functions */
 char* fuzzer_get_tmpfile (int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  fuzzer_release_tmpfile (char*) ; 
 int /*<<< orphan*/  tidyCreate () ; 
 int /*<<< orphan*/  tidyLoadConfig (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  tidyRelease (int /*<<< orphan*/ ) ; 

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    TidyDoc tdoc = tidyCreate();

    // At the time this fuzzer was written, the configuration parser could
    // only be exercised via a file interface.
    char* tmpfile = fuzzer_get_tmpfile(data, size);
    tidyLoadConfig(tdoc, tmpfile);
    fuzzer_release_tmpfile(tmpfile);
    tidyRelease(tdoc);
    return 0;
}
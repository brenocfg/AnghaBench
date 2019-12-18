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
typedef  int /*<<< orphan*/  TidyDoc ;
typedef  int /*<<< orphan*/  TidyBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  TidyForceOutput ; 
 int /*<<< orphan*/  TidyXhtmlOut ; 
 int /*<<< orphan*/  abort () ; 
 scalar_t__ tidyCleanAndRepair (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tidyCreate () ; 
 int /*<<< orphan*/  tidyOptSetBool (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ tidyParseBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tidyRelease (int /*<<< orphan*/ ) ; 
 scalar_t__ tidyRunDiagnostics (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tidySaveBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ tidySetErrorBuffer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  yes ; 

void run_tidy_parser(TidyBuffer* data_buffer,
                     TidyBuffer* output_buffer,
                     TidyBuffer* error_buffer) {
    TidyDoc tdoc = tidyCreate();
    if (tidySetErrorBuffer(tdoc, error_buffer) < 0) {
        abort();
    }
    tidyOptSetBool(tdoc, TidyXhtmlOut, yes);
    tidyOptSetBool(tdoc, TidyForceOutput, yes);

    if (tidyParseBuffer(tdoc, data_buffer) >= 0 &&
            tidyCleanAndRepair(tdoc) >= 0 &&
            tidyRunDiagnostics(tdoc) >= 0) {
        tidySaveBuffer(tdoc, output_buffer);
    }
    tidyRelease(tdoc);
}
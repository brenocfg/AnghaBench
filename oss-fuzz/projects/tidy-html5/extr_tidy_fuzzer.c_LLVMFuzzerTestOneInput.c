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
typedef  int /*<<< orphan*/  byte ;
typedef  int /*<<< orphan*/  TidyBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  run_tidy_parser (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tidyBufAttach (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  tidyBufDetach (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tidyBufFree (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tidyBufInit (int /*<<< orphan*/ *) ; 

int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    TidyBuffer data_buffer;
    TidyBuffer output_buffer;
    TidyBuffer error_buffer;
    tidyBufInit(&data_buffer);
    tidyBufInit(&output_buffer);
    tidyBufInit(&error_buffer);

    tidyBufAttach(&data_buffer, (byte*)data, size);
    run_tidy_parser(&data_buffer, &output_buffer, &error_buffer);

    tidyBufFree(&error_buffer);
    tidyBufFree(&output_buffer);
    tidyBufDetach(&data_buffer);
    return 0;
}
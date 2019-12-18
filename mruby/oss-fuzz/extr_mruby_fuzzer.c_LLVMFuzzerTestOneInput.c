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
typedef  int /*<<< orphan*/  mrb_state ;

/* Variables and functions */
 int /*<<< orphan*/  free (char*) ; 
 char* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (char*,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  mrb_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mrb_load_string (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * mrb_open () ; 

int LLVMFuzzerTestOneInput(uint8_t *Data, size_t size) {
    if (size < 1) {
        return 0;
    }
    char *code = malloc(size+1);
    memcpy(code, Data, size);
    code[size] = '\0';
    mrb_state *mrb = mrb_open();
    mrb_load_string(mrb, code);
    mrb_close(mrb);
    free(code);
    return 0;
}
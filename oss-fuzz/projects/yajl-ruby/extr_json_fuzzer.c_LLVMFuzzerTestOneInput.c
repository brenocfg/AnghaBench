#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int allowComments; int checkUTF8; } ;
typedef  TYPE_1__ yajl_parser_config ;
typedef  int /*<<< orphan*/  yajl_handle ;
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {int /*<<< orphan*/  objectLevel; int /*<<< orphan*/  arrayLevel; } ;
typedef  TYPE_2__ context ;

/* Variables and functions */
 int /*<<< orphan*/  callbacks ; 
 int /*<<< orphan*/  yajl_alloc (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  yajl_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  yajl_parse (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,size_t) ; 

int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
    context ctx = {
        .arrayLevel = 0,
        .objectLevel = 0,
    };
    yajl_parser_config cfg = {
        .allowComments = 1,
        .checkUTF8 = 1,
    };
    yajl_handle parser = yajl_alloc(&callbacks, &cfg, NULL, (void*)&ctx);

    (void)yajl_parse(parser, data, size);
    yajl_free(parser);

    return 0;
}
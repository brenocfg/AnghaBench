#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
#define  CHANNEL 130 
 int /*<<< orphan*/  OSSL_TRACE2 (int /*<<< orphan*/ ,char*,char const*,int /*<<< orphan*/ ) ; 
#define  PREFIX 129 
#define  SUFFIX 128 
 int /*<<< orphan*/  TRACE ; 
 TYPE_1__* trace_categories ; 

__attribute__((used)) static int trace_attach_w_callback_cb(int category, int type, const void *data)
{
    switch (type) {
    case CHANNEL:
        OSSL_TRACE2(TRACE,
                    "Attach channel %p to category '%s' (with callback)\n",
                    data, trace_categories[category].name);
        break;
    case PREFIX:
        OSSL_TRACE2(TRACE, "Attach prefix \"%s\" to category '%s'\n",
                    (const char *)data, trace_categories[category].name);
        break;
    case SUFFIX:
        OSSL_TRACE2(TRACE, "Attach suffix \"%s\" to category '%s'\n",
                    (const char *)data, trace_categories[category].name);
        break;
    default:                     /* No clue */
        break;
    }
    return 1;
}
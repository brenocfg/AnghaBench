#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  params; } ;
struct TYPE_7__ {char* param_name; int /*<<< orphan*/ * param_value; } ;
typedef  TYPE_1__ MIME_PARAM ;
typedef  TYPE_2__ MIME_HEADER ;

/* Variables and functions */
 int sk_MIME_PARAM_find (int /*<<< orphan*/ ,TYPE_1__*) ; 
 TYPE_1__* sk_MIME_PARAM_value (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static MIME_PARAM *mime_param_find(MIME_HEADER *hdr, const char *name)
{
    MIME_PARAM param;
    int idx;

    param.param_name = (char *)name;
    param.param_value = NULL;
    idx = sk_MIME_PARAM_find(hdr->params, &param);
    return sk_MIME_PARAM_value(hdr->params, idx);
}
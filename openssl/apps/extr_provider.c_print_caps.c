#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  settable_ctx_params; int /*<<< orphan*/  gettable_ctx_params; int /*<<< orphan*/  gettable_params; } ;
struct TYPE_6__ {int verbose; scalar_t__ first; int /*<<< orphan*/  subindent; int /*<<< orphan*/  label; int /*<<< orphan*/  indent; int /*<<< orphan*/  total; } ;
typedef  TYPE_1__ META ;
typedef  TYPE_2__ INFO ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_printf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  bio_out ; 
 int /*<<< orphan*/  print_method_names (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  print_param_types (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void print_caps(META *meta, INFO *info)
{
    switch (meta->verbose) {
    case 1:
        if (!meta->first)
            BIO_printf(bio_out, "; ");
        print_method_names(bio_out, info);
        break;
    case 2:
        if (meta->first) {
            if (meta->total > 0)
                BIO_printf(bio_out, "\n");
            BIO_printf(bio_out, "%*s%ss:", meta->indent, "", meta->label);
        }
        BIO_printf(bio_out, " ");
        print_method_names(bio_out, info);
        break;
    case 3:
    default:
        BIO_printf(bio_out, "%*s%s ", meta->indent, "", meta->label);
        print_method_names(bio_out, info);
        BIO_printf(bio_out, "\n");
        print_param_types("retrievable algorithm parameters",
                          info->gettable_params, meta->subindent);
        print_param_types("retrievable operation parameters",
                          info->gettable_ctx_params, meta->subindent);
        print_param_types("settable operation parameters",
                          info->settable_ctx_params, meta->subindent);
        break;
    }
    meta->first = 0;
}
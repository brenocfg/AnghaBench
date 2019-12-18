#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  njs_vm_t ;
struct TYPE_8__ {int /*<<< orphan*/  external; } ;
typedef  TYPE_1__ njs_vm_opt_t ;
typedef  size_t njs_uint_t ;
struct TYPE_9__ {size_t length; int /*<<< orphan*/ * start; } ;
typedef  TYPE_2__ njs_str_t ;
struct TYPE_10__ {size_t n_paths; int /*<<< orphan*/ ** paths; } ;
typedef  TYPE_3__ njs_opts_t ;
typedef  scalar_t__ njs_int_t ;

/* Variables and functions */
 scalar_t__ NJS_OK ; 
 scalar_t__ getenv (char*) ; 
 scalar_t__ njs_externals_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  njs_stderror (char*) ; 
 int /*<<< orphan*/ * njs_strchr (int /*<<< orphan*/ *,char) ; 
 size_t njs_strlen (int /*<<< orphan*/ *) ; 
 scalar_t__ njs_vm_add_path (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/ * njs_vm_create (TYPE_1__*) ; 

__attribute__((used)) static njs_vm_t *
njs_create_vm(njs_opts_t *opts, njs_vm_opt_t *vm_options)
{
    u_char      *p, *start;
    njs_vm_t    *vm;
    njs_int_t   ret;
    njs_str_t   path;
    njs_uint_t  i;

    vm = njs_vm_create(vm_options);
    if (vm == NULL) {
        njs_stderror("failed to create vm\n");
        return NULL;
    }

    if (njs_externals_init(vm, vm_options->external) != NJS_OK) {
        njs_stderror("failed to add external protos\n");
        return NULL;
    }

    for (i = 0; i < opts->n_paths; i++) {
        path.start = (u_char *) opts->paths[i];
        path.length = njs_strlen(opts->paths[i]);

        ret = njs_vm_add_path(vm, &path);
        if (ret != NJS_OK) {
            njs_stderror("failed to add path\n");
            return NULL;
        }
    }

    start = (u_char *) getenv("NJS_PATH");
    if (start == NULL) {
        return vm;
    }

    for ( ;; ) {
        p = njs_strchr(start, ':');

        path.start = start;
        path.length = (p != NULL) ? (size_t) (p - start) : njs_strlen(start);

        ret = njs_vm_add_path(vm, &path);
        if (ret != NJS_OK) {
            njs_stderror("failed to add path\n");
            return NULL;
        }

        if (p == NULL) {
            break;
        }

        start = p + 1;
    }

    return vm;
}
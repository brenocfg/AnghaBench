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
struct TYPE_5__ {scalar_t__ modified_props; scalar_t__ port; int /*<<< orphan*/  has_port; scalar_t__ username_len; int /*<<< orphan*/ * username; scalar_t__ scheme_len; int /*<<< orphan*/ * scheme; scalar_t__ query_len; int /*<<< orphan*/ * query; scalar_t__ path_len; int /*<<< orphan*/ * path; scalar_t__ password_len; int /*<<< orphan*/ * password; scalar_t__ host_len; int /*<<< orphan*/ * host; scalar_t__ fragment_len; int /*<<< orphan*/ * fragment; TYPE_1__* uri; } ;
typedef  TYPE_2__ UriBuilder ;
struct TYPE_4__ {int /*<<< orphan*/  IUri_iface; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IUri_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void reset_builder(UriBuilder *builder) {
    if(builder->uri)
        IUri_Release(&builder->uri->IUri_iface);
    builder->uri = NULL;

    heap_free(builder->fragment);
    builder->fragment = NULL;
    builder->fragment_len = 0;

    heap_free(builder->host);
    builder->host = NULL;
    builder->host_len = 0;

    heap_free(builder->password);
    builder->password = NULL;
    builder->password_len = 0;

    heap_free(builder->path);
    builder->path = NULL;
    builder->path_len = 0;

    heap_free(builder->query);
    builder->query = NULL;
    builder->query_len = 0;

    heap_free(builder->scheme);
    builder->scheme = NULL;
    builder->scheme_len = 0;

    heap_free(builder->username);
    builder->username = NULL;
    builder->username_len = 0;

    builder->has_port = FALSE;
    builder->port = 0;
    builder->modified_props = 0;
}
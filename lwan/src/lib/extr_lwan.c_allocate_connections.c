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
struct lwan_connection {int dummy; } ;
struct lwan {int /*<<< orphan*/  conns; } ;

/* Variables and functions */
 scalar_t__ UNLIKELY (int) ; 
 int /*<<< orphan*/  lwan_aligned_alloc (size_t const,int) ; 
 int /*<<< orphan*/  lwan_status_critical_perror (char*) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t const) ; 

__attribute__((used)) static void allocate_connections(struct lwan *l, size_t max_open_files)
{
    const size_t sz = max_open_files * sizeof(struct lwan_connection);

    l->conns = lwan_aligned_alloc(sz, 64);
    if (UNLIKELY(!l->conns))
        lwan_status_critical_perror("lwan_alloc_aligned");

    memset(l->conns, 0, sz);
}
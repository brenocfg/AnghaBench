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
struct TYPE_4__ {int /*<<< orphan*/  cookie; scalar_t__ (* read_fn ) (int /*<<< orphan*/ ,void*,size_t) ;} ;
struct priv {TYPE_1__ info; } ;
struct TYPE_5__ {struct priv* priv; } ;
typedef  TYPE_2__ stream_t ;

/* Variables and functions */
 scalar_t__ stub1 (int /*<<< orphan*/ ,void*,size_t) ; 

__attribute__((used)) static int fill_buffer(stream_t *s, void *buffer, int max_len)
{
    struct priv *p = s->priv;
    return (int)p->info.read_fn(p->info.cookie, buffer, (size_t)max_len);
}
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
typedef  int /*<<< orphan*/  uint16_t ;
struct wspace {void* errlocs; void* derrlocs; void* s; void* corr; void* r; void* c; } ;
struct rs_codec {int nroots; int nn; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  free_ws (struct wspace*) ; 
 void* kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 struct wspace* kzalloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct wspace *alloc_ws(struct rs_codec *rs)
{
	int nroots = rs->nroots;
	struct wspace *ws;
	int nn = rs->nn;

	ws = kzalloc(sizeof(*ws), GFP_KERNEL);
	if (!ws)
		return NULL;

	ws->c = kmalloc_array(2 * (nn + nroots),
				sizeof(uint16_t), GFP_KERNEL);
	if (!ws->c)
		goto err;

	ws->r = ws->c + nn;
	ws->s = ws->r + nn;
	ws->corr = ws->s + nroots;

	ws->errlocs = kmalloc_array(nn + nroots, sizeof(int), GFP_KERNEL);
	if (!ws->errlocs)
		goto err;

	ws->derrlocs = ws->errlocs + nn;
	return ws;

err:
	free_ws(ws);
	return NULL;
}
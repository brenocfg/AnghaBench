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
struct sdio_func {int dummy; } ;
struct dvobj_priv {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  devobj_deinit (struct dvobj_priv*) ; 
 int /*<<< orphan*/  sdio_deinit (struct dvobj_priv*) ; 
 struct dvobj_priv* sdio_get_drvdata (struct sdio_func*) ; 
 int /*<<< orphan*/  sdio_set_drvdata (struct sdio_func*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sdio_dvobj_deinit(struct sdio_func *func)
{
	struct dvobj_priv *dvobj = sdio_get_drvdata(func);

	sdio_set_drvdata(func, NULL);
	if (dvobj) {
		sdio_deinit(dvobj);
		devobj_deinit(dvobj);
	}
	return;
}
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
typedef  int /*<<< orphan*/  uint8 ;
typedef  int /*<<< orphan*/  PushFilter ;
typedef  int /*<<< orphan*/  PX_MD ;

/* Variables and functions */
 int pushf_write (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  px_md_update (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int
mdc_write(PushFilter *dst, void *priv, const uint8 *data, int len)
{
	PX_MD	   *md = priv;

	px_md_update(md, data, len);
	return pushf_write(dst, data, len);
}
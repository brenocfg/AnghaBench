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
struct buf_ref_priv {int cur; int size; } ;
typedef  int st64 ;
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
#define  R_BUF_CUR 130 
#define  R_BUF_END 129 
#define  R_BUF_SET 128 
 struct buf_ref_priv* get_priv_ref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_warn_if_reached () ; 

__attribute__((used)) static st64 buf_ref_seek(RBuffer *b, st64 addr, int whence) {
	struct buf_ref_priv *priv = get_priv_ref (b);
	switch (whence) {
	case R_BUF_CUR:
		priv->cur += addr;
		break;
	case R_BUF_SET:
		priv->cur = addr;
		break;
	case R_BUF_END:
		priv->cur = priv->size + addr;
		break;
	default:
		r_warn_if_reached ();
		return -1;
	}
	return priv->cur;
}
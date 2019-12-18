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
typedef  int /*<<< orphan*/  ut8 ;
typedef  int /*<<< orphan*/  ut64 ;
struct buf_file_priv {int /*<<< orphan*/  fd; } ;
typedef  int /*<<< orphan*/  st64 ;
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
 struct buf_file_priv* get_priv_file (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_sandbox_write (int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static st64 buf_file_write(RBuffer *b, const ut8 *buf, ut64 len) {
	struct buf_file_priv *priv = get_priv_file (b);
	return r_sandbox_write (priv->fd, buf, len);
}
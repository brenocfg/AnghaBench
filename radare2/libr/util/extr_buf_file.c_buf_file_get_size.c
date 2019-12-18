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
typedef  int /*<<< orphan*/  ut64 ;
struct buf_file_priv {int /*<<< orphan*/  fd; } ;
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  SEEK_END ; 
 int /*<<< orphan*/  SEEK_SET ; 
 struct buf_file_priv* get_priv_file (int /*<<< orphan*/ *) ; 
 int r_sandbox_lseek (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ut64 buf_file_get_size(RBuffer *b) {
	struct buf_file_priv *priv = get_priv_file (b);
	int pos = r_sandbox_lseek (priv->fd, 0, SEEK_CUR);
	int res = r_sandbox_lseek (priv->fd, 0, SEEK_END);
	r_sandbox_lseek (priv->fd, pos, SEEK_SET);
	return (ut64)res;
}
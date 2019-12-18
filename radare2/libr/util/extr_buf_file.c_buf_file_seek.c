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
struct buf_file_priv {int /*<<< orphan*/  fd; } ;
typedef  int /*<<< orphan*/  st64 ;
typedef  int /*<<< orphan*/  RBuffer ;

/* Variables and functions */
#define  R_BUF_CUR 130 
#define  R_BUF_END 129 
#define  R_BUF_SET 128 
 int SEEK_CUR ; 
 int SEEK_END ; 
 int SEEK_SET ; 
 struct buf_file_priv* get_priv_file (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  r_sandbox_lseek (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static st64 buf_file_seek(RBuffer *b, st64 addr, int whence) {
	struct buf_file_priv *priv = get_priv_file (b);
	switch (whence) {
	case R_BUF_CUR: whence = SEEK_CUR; break;
	case R_BUF_SET: whence = SEEK_SET; break;
	case R_BUF_END: whence = SEEK_END; break;
	}
	return r_sandbox_lseek (priv->fd, addr, whence);
}
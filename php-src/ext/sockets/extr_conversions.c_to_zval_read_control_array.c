#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int uint32_t ;
struct msghdr {int dummy; } ;
struct cmsghdr {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/  has_error; } ;
struct TYPE_6__ {int /*<<< orphan*/  keys; TYPE_1__ err; } ;
typedef  TYPE_2__ res_context ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 struct cmsghdr* CMSG_FIRSTHDR (struct msghdr*) ; 
 struct cmsghdr* CMSG_NXTHDR (struct msghdr*,struct cmsghdr*) ; 
 int /*<<< orphan*/  ZVAL_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_ARRVAL_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  array_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 scalar_t__ snprintf (char*,int,char*,unsigned int) ; 
 int /*<<< orphan*/  to_zval_read_control (char const*,int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/ * zend_hash_next_index_insert (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_llist_add_element (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  zend_llist_remove_tail (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void to_zval_read_control_array(const char *msghdr_c, zval *zv, res_context *ctx)
{
	struct msghdr	*msg = (struct msghdr *)msghdr_c;
	struct cmsghdr	*cmsg;
	char			buf[sizeof("element #4294967295")];
	char			*bufp = buf;
	uint32_t		i = 1;

	array_init(zv);

	for (cmsg = CMSG_FIRSTHDR(msg);
			cmsg != NULL && !ctx->err.has_error;
			cmsg = CMSG_NXTHDR(msg, cmsg)) {
		zval *elem, tmp;

		ZVAL_NULL(&tmp);
		elem = zend_hash_next_index_insert(Z_ARRVAL_P(zv), &tmp);

		if ((size_t)snprintf(buf, sizeof(buf), "element #%u", (unsigned)i++) >= sizeof(buf)) {
			memcpy(buf, "element", sizeof("element"));
		}
		zend_llist_add_element(&ctx->keys, &bufp);

		to_zval_read_control((const char *)cmsg, elem, ctx);

		zend_llist_remove_tail(&ctx->keys);
	}
}
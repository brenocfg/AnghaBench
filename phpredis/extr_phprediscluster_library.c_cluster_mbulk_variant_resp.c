#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_3__ {int type; int len; int elements; struct TYPE_3__** element; int /*<<< orphan*/  str; int /*<<< orphan*/  integer; } ;
typedef  TYPE_1__ clusterReply ;

/* Variables and functions */
#define  TYPE_BULK 131 
#define  TYPE_INT 130 
#define  TYPE_LINE 129 
#define  TYPE_MULTIBULK 128 
 int /*<<< orphan*/  add_next_index_bool (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  add_next_index_long (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_next_index_null (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_next_index_stringl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  add_next_index_zval (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  array_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cluster_mbulk_variant_resp(clusterReply *r, zval *z_ret)
{
    zval z_sub_ele;
    int i;

    switch(r->type) {
        case TYPE_INT:
            add_next_index_long(z_ret, r->integer);
            break;
        case TYPE_LINE:
            if (r->str) {
                add_next_index_stringl(z_ret, r->str, r->len);
            } else {
                add_next_index_bool(z_ret, 1);
            }
            break;
        case TYPE_BULK:
            if (r->len > -1) {
                add_next_index_stringl(z_ret, r->str, r->len);
            } else {
                add_next_index_null(z_ret);
            }
            break;
        case TYPE_MULTIBULK:
            array_init(&z_sub_ele);
            for (i = 0; i < r->elements; i++) {
                cluster_mbulk_variant_resp(r->element[i], &z_sub_ele);
            }
            add_next_index_zval(z_ret, &z_sub_ele);
            break;
        default:
            add_next_index_bool(z_ret, 0);
            break;
    }
}
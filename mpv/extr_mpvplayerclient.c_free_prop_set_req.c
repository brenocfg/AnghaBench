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
struct setproperty_request {int /*<<< orphan*/  data; int /*<<< orphan*/  format; } ;
struct m_option {int dummy; } ;

/* Variables and functions */
 struct m_option* get_mp_type (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  m_option_free (struct m_option const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void free_prop_set_req(void *ptr)
{
    struct setproperty_request *req = ptr;
    const struct m_option *type = get_mp_type(req->format);
    m_option_free(type, req->data);
}
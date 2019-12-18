#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct ucred {int dummy; } ;
struct in6_pktinfo {int dummy; } ;
typedef  int /*<<< orphan*/  ancillary_reg_entry ;
typedef  int /*<<< orphan*/  anc_reg_key ;
struct TYPE_2__ {int initialized; int /*<<< orphan*/  ht; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_IPV6 ; 
 int /*<<< orphan*/  IPV6_HOPLIMIT ; 
 int /*<<< orphan*/  IPV6_PKTINFO ; 
 int /*<<< orphan*/  IPV6_TCLASS ; 
 int /*<<< orphan*/  PUT_ENTRY (int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SCM_CREDENTIALS ; 
 int /*<<< orphan*/  SCM_RIGHTS ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  ancillary_registery_free_elem ; 
 TYPE_1__ ancillary_registry ; 
 int /*<<< orphan*/  calculate_scm_rights_space ; 
 int /*<<< orphan*/  from_zval_write_fd_array ; 
 int /*<<< orphan*/  from_zval_write_in6_pktinfo ; 
 int /*<<< orphan*/  from_zval_write_int ; 
 int /*<<< orphan*/  from_zval_write_ucred ; 
 int /*<<< orphan*/  to_zval_read_fd_array ; 
 int /*<<< orphan*/  to_zval_read_in6_pktinfo ; 
 int /*<<< orphan*/  to_zval_read_int ; 
 int /*<<< orphan*/  to_zval_read_ucred ; 
 int /*<<< orphan*/  zend_hash_init (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void init_ancillary_registry(void)
{
	ancillary_reg_entry entry;
	anc_reg_key key;
	ancillary_registry.initialized = 1;

	zend_hash_init(&ancillary_registry.ht, 32, NULL, ancillary_registery_free_elem, 1);

#define PUT_ENTRY(sizev, var_size, calc, from, to, level, type) \
	entry.size			= sizev; \
	entry.var_el_size	= var_size; \
	entry.calc_space	= calc; \
	entry.from_array	= from; \
	entry.to_array		= to; \
	key.cmsg_level		= level; \
	key.cmsg_type		= type; \
	zend_hash_str_update_mem(&ancillary_registry.ht, (char*)&key, sizeof(key), (void*)&entry, sizeof(entry))

#if defined(IPV6_PKTINFO) && HAVE_IPV6
	PUT_ENTRY(sizeof(struct in6_pktinfo), 0, 0, from_zval_write_in6_pktinfo,
			to_zval_read_in6_pktinfo, IPPROTO_IPV6, IPV6_PKTINFO);
#endif

#if defined(IPV6_HOPLIMIT) && HAVE_IPV6
	PUT_ENTRY(sizeof(int), 0, 0, from_zval_write_int,
			to_zval_read_int, IPPROTO_IPV6, IPV6_HOPLIMIT);
#endif

#if defined(IPV6_TCLASS) && HAVE_IPV6
	PUT_ENTRY(sizeof(int), 0, 0, from_zval_write_int,
			to_zval_read_int, IPPROTO_IPV6, IPV6_TCLASS);
#endif

#ifdef SO_PASSCRED
	PUT_ENTRY(sizeof(struct ucred), 0, 0, from_zval_write_ucred,
			to_zval_read_ucred, SOL_SOCKET, SCM_CREDENTIALS);
#endif

#ifdef SCM_RIGHTS
	PUT_ENTRY(0, sizeof(int), calculate_scm_rights_space, from_zval_write_fd_array,
			to_zval_read_fd_array, SOL_SOCKET, SCM_RIGHTS);
#endif

}
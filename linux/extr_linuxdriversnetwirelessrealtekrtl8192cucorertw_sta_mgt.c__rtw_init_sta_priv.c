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
typedef  int /*<<< orphan*/  u32 ;
struct sta_priv {int /*<<< orphan*/  free_sta_queue; int /*<<< orphan*/ * sta_hash; scalar_t__ pstainfo_buf; int /*<<< orphan*/  wakeup_q; int /*<<< orphan*/  sleep_q; scalar_t__ asoc_sta_count; int /*<<< orphan*/  sta_hash_lock; scalar_t__ pallocated_stainfo_buf; } ;
struct sta_info {int /*<<< orphan*/  list; } ;
typedef  int s32 ;
typedef  int SIZE_PTR ;

/* Variables and functions */
 int NUM_STA ; 
 int /*<<< orphan*/  _FAIL ; 
 int /*<<< orphan*/  _SUCCESS ; 
 int /*<<< orphan*/  _func_enter_ ; 
 int /*<<< orphan*/  _func_exit_ ; 
 int /*<<< orphan*/  _rtw_init_listhead (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _rtw_init_queue (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  _rtw_init_stainfo (struct sta_info*) ; 
 int /*<<< orphan*/  _rtw_spinlock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_list_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtw_list_insert_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ rtw_zvmalloc (int) ; 

u32	_rtw_init_sta_priv(struct	sta_priv *pstapriv)
{
	struct sta_info *psta;
	s32 i;

_func_enter_;	

	pstapriv->pallocated_stainfo_buf = rtw_zvmalloc (sizeof(struct sta_info) * NUM_STA+ 4);
	
	if(!pstapriv->pallocated_stainfo_buf)
		return _FAIL;

	pstapriv->pstainfo_buf = pstapriv->pallocated_stainfo_buf + 4 - 
		((SIZE_PTR)(pstapriv->pallocated_stainfo_buf ) & 3);

	_rtw_init_queue(&pstapriv->free_sta_queue);

	_rtw_spinlock_init(&pstapriv->sta_hash_lock);
	
	//_rtw_init_queue(&pstapriv->asoc_q);
	pstapriv->asoc_sta_count = 0;
	_rtw_init_queue(&pstapriv->sleep_q);
	_rtw_init_queue(&pstapriv->wakeup_q);

	psta = (struct sta_info *)(pstapriv->pstainfo_buf);

		
	for(i = 0; i < NUM_STA; i++)
	{
		_rtw_init_stainfo(psta);

		_rtw_init_listhead(&(pstapriv->sta_hash[i]));

		rtw_list_insert_tail(&psta->list, get_list_head(&pstapriv->free_sta_queue));

		psta++;
	}

	

#ifdef CONFIG_AP_MODE

	pstapriv->sta_dz_bitmap = 0;
	pstapriv->tim_bitmap = 0;

	_rtw_init_listhead(&pstapriv->asoc_list);
	_rtw_init_listhead(&pstapriv->auth_list);
	_rtw_spinlock_init(&pstapriv->asoc_list_lock);
	_rtw_spinlock_init(&pstapriv->auth_list_lock);
	pstapriv->asoc_list_cnt = 0;
	pstapriv->auth_list_cnt = 0;

	pstapriv->auth_to = 3; // 3*2 = 6 sec 
	pstapriv->assoc_to = 3;
	//pstapriv->expire_to = 900;// 900*2 = 1800 sec = 30 min, expire after no any traffic.
	//pstapriv->expire_to = 30;// 30*2 = 60 sec = 1 min, expire after no any traffic.
#ifdef CONFIG_ACTIVE_KEEP_ALIVE_CHECK
	pstapriv->expire_to = 3; // 3*2 = 6 sec
#else
	pstapriv->expire_to = 60;// 60*2 = 120 sec = 2 min, expire after no any traffic.
#endif	
	pstapriv->max_num_sta = NUM_STA;
		
#endif
	
_func_exit_;		

	return _SUCCESS;
	
}
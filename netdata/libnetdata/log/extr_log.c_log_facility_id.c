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

/* Variables and functions */
 int LOG_AUTH ; 
 int LOG_AUTHPRIV ; 
 char const* LOG_AUTHPRIV_KEY ; 
 char const* LOG_AUTH_KEY ; 
 int LOG_CONSOLE ; 
 char const* LOG_CONSOLE_KEY ; 
 int LOG_CRON ; 
 char const* LOG_CRON_KEY ; 
 int LOG_DAEMON ; 
 char const* LOG_DAEMON_KEY ; 
 int LOG_FTP ; 
 char const* LOG_FTP_KEY ; 
 int LOG_INSTALL ; 
 char const* LOG_INSTALL_KEY ; 
 int LOG_KERN ; 
 char const* LOG_KERN_KEY ; 
 int LOG_LAUNCHD ; 
 char const* LOG_LAUNCHD_KEY ; 
 int LOG_LOCAL0 ; 
 char const* LOG_LOCAL0_KEY ; 
 int LOG_LOCAL1 ; 
 char const* LOG_LOCAL1_KEY ; 
 int LOG_LOCAL2 ; 
 char const* LOG_LOCAL2_KEY ; 
 int LOG_LOCAL3 ; 
 char const* LOG_LOCAL3_KEY ; 
 int LOG_LOCAL4 ; 
 char const* LOG_LOCAL4_KEY ; 
 int LOG_LOCAL5 ; 
 char const* LOG_LOCAL5_KEY ; 
 int LOG_LOCAL6 ; 
 char const* LOG_LOCAL6_KEY ; 
 int LOG_LOCAL7 ; 
 char const* LOG_LOCAL7_KEY ; 
 int LOG_LPR ; 
 char const* LOG_LPR_KEY ; 
 int LOG_MAIL ; 
 char const* LOG_MAIL_KEY ; 
 int LOG_NETINFO ; 
 char const* LOG_NETINFO_KEY ; 
 int LOG_NEWS ; 
 char const* LOG_NEWS_KEY ; 
 int LOG_NTP ; 
 char const* LOG_NTP_KEY ; 
 int LOG_RAS ; 
 char const* LOG_RAS_KEY ; 
 int LOG_REMOTEAUTH ; 
 char const* LOG_REMOTEAUTH_KEY ; 
 int LOG_SECURITY ; 
 char const* LOG_SECURITY_KEY ; 
 int LOG_SYSLOG ; 
 char const* LOG_SYSLOG_KEY ; 
 int LOG_USER ; 
 char const* LOG_USER_KEY ; 
 int LOG_UUCP ; 
 char const* LOG_UUCP_KEY ; 
 int simple_hash (char const*) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int log_facility_id(const char *facility_name)
{
	static int 
		hash_auth = 0,
		hash_authpriv = 0,
#ifdef __FreeBSD__
		hash_console = 0,
#endif
		hash_cron = 0,
		hash_daemon = 0,
		hash_ftp = 0,
#ifdef __APPLE__
		hash_install = 0,
#endif
		hash_kern = 0,
		hash_lpr = 0,
		hash_mail = 0,
//		hash_mark = 0,
#ifdef __APPLE__
		hash_netinfo = 0,
		hash_ras = 0,
		hash_remoteauth = 0,
#endif
		hash_news = 0,
#ifdef __FreeBSD__
		hash_ntp = 0,
#endif
		hash_security = 0,
		hash_syslog = 0,
		hash_user = 0,
		hash_uucp = 0,
#ifdef __APPLE__
		hash_launchd = 0,
#endif
		hash_local0 = 0,
		hash_local1 = 0,
		hash_local2 = 0,
		hash_local3 = 0,
		hash_local4 = 0,
		hash_local5 = 0,
		hash_local6 = 0,
		hash_local7 = 0;

	if(unlikely(!hash_auth))
	{
		hash_auth = simple_hash(LOG_AUTH_KEY);
		hash_authpriv = simple_hash(LOG_AUTHPRIV_KEY);
#ifdef __FreeBSD__
		hash_console = simple_hash(LOG_CONSOLE_KEY);
#endif
		hash_cron = simple_hash(LOG_CRON_KEY);
		hash_daemon = simple_hash(LOG_DAEMON_KEY);
		hash_ftp = simple_hash(LOG_FTP_KEY);
#ifdef __APPLE__
		hash_install = simple_hash(LOG_INSTALL_KEY);
#endif
		hash_kern = simple_hash(LOG_KERN_KEY);
		hash_lpr = simple_hash(LOG_LPR_KEY);
		hash_mail = simple_hash(LOG_MAIL_KEY);
//		hash_mark = simple_uhash();
#ifdef __APPLE__
		hash_netinfo = simple_hash(LOG_NETINFO_KEY);
		hash_ras = simple_hash(LOG_RAS_KEY);
		hash_remoteauth = simple_hash(LOG_REMOTEAUTH_KEY);
#endif
		hash_news = simple_hash(LOG_NEWS_KEY);
#ifdef __FreeBSD__
		hash_ntp = simple_hash(LOG_NTP_KEY);
#endif
		hash_security = simple_hash(LOG_SECURITY_KEY);
		hash_syslog = simple_hash(LOG_SYSLOG_KEY);
		hash_user = simple_hash(LOG_USER_KEY);
		hash_uucp = simple_hash(LOG_UUCP_KEY);
#ifdef __APPLE__
		hash_launchd = simple_hash(LOG_LAUNCHD_KEY);
#endif
		hash_local0 = simple_hash(LOG_LOCAL0_KEY);
		hash_local1 = simple_hash(LOG_LOCAL1_KEY);
		hash_local2 = simple_hash(LOG_LOCAL2_KEY);
		hash_local3 = simple_hash(LOG_LOCAL3_KEY);
		hash_local4 = simple_hash(LOG_LOCAL4_KEY);
		hash_local5 = simple_hash(LOG_LOCAL5_KEY);
		hash_local6 = simple_hash(LOG_LOCAL6_KEY);
		hash_local7 = simple_hash(LOG_LOCAL7_KEY);
	}

	int hash = simple_hash(facility_name);
	if ( hash == hash_auth )
	{
		return LOG_AUTH;
	}
	else if  ( hash == hash_authpriv )
	{
		return LOG_AUTHPRIV;
	}
#ifdef __FreeBSD__
	else if ( hash == hash_console )
	{
		return LOG_CONSOLE;
	}
#endif
	else if ( hash == hash_cron )
	{
		return LOG_CRON;
	}
	else if ( hash == hash_daemon )
	{
		return LOG_DAEMON;
	}
	else if ( hash == hash_ftp )
	{
		return LOG_FTP;
	}
#ifdef __APPLE__
	else if ( hash == hash_install )
	{
		return LOG_INSTALL;
	}
#endif
	else if ( hash == hash_kern )
	{
		return LOG_KERN;
	}
	else if ( hash == hash_lpr )
	{
		return LOG_LPR;
	}
	else if ( hash == hash_mail )
	{
		return LOG_MAIL;
	}
	/*
	else if ( hash == hash_mark )
	{
		//this is internal for all OS
		return INTERNAL_MARK;
	}
	*/
#ifdef __APPLE__
	else if ( hash == hash_netinfo )
	{
		return LOG_NETINFO;
	}
	else if ( hash == hash_ras )
	{
		return LOG_RAS;
	}
	else if ( hash == hash_remoteauth )
	{
		return LOG_REMOTEAUTH;
	}
#endif
	else if ( hash == hash_news )
	{
		return LOG_NEWS;
	}
#ifdef __FreeBSD__
	else if ( hash == hash_ntp )
	{
		return LOG_NTP;
	}
#endif
	else if ( hash == hash_security )
	{
		//FreeBSD is the unique that does not consider
		//this facility deprecated. We are keeping
		//it for other OS while they are kept in their headers.
#ifdef __FreeBSD__
		return LOG_SECURITY;
#else
		return LOG_AUTH;
#endif
	}
	else if ( hash == hash_syslog )
	{
		return LOG_SYSLOG;
	}
	else if ( hash == hash_user )
	{
		return LOG_USER;
	}
	else if ( hash == hash_uucp )
	{
		return LOG_UUCP;
	}
	else if ( hash == hash_local0 )
	{
		return LOG_LOCAL0;
	}
	else if ( hash == hash_local1 )
	{
		return LOG_LOCAL1;
	}
	else if ( hash == hash_local2 )
	{
		return LOG_LOCAL2;
	}
	else if ( hash == hash_local3 )
	{
		return LOG_LOCAL3;
	}
	else if ( hash == hash_local4 )
	{
		return LOG_LOCAL4;
	}
	else if ( hash == hash_local5 )
	{
		return LOG_LOCAL5;
	}
	else if ( hash == hash_local6 )
	{
		return LOG_LOCAL6;
	}
	else if ( hash == hash_local7 )
	{
		return LOG_LOCAL7;
	}
#ifdef __APPLE__
	else if ( hash == hash_launchd )
	{
		return LOG_LAUNCHD;
	}
#endif

	return LOG_DAEMON;
}
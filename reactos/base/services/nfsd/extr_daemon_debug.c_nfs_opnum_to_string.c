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
#define  OP_ACCESS 184 
#define  OP_BACKCHANNEL_CTL 183 
#define  OP_BIND_CONN_TO_SESSION 182 
#define  OP_CLOSE 181 
#define  OP_COMMIT 180 
#define  OP_CREATE 179 
#define  OP_CREATE_SESSION 178 
#define  OP_DELEGPURGE 177 
#define  OP_DELEGRETURN 176 
#define  OP_DESTROY_CLIENTID 175 
#define  OP_DESTROY_SESSION 174 
#define  OP_EXCHANGE_ID 173 
#define  OP_FREE_STATEID 172 
#define  OP_GETATTR 171 
#define  OP_GETDEVICEINFO 170 
#define  OP_GETDEVICELIST 169 
#define  OP_GETFH 168 
#define  OP_GET_DIR_DELEGATION 167 
#define  OP_ILLEGAL 166 
#define  OP_LAYOUTCOMMIT 165 
#define  OP_LAYOUTGET 164 
#define  OP_LAYOUTRETURN 163 
#define  OP_LINK 162 
#define  OP_LOCK 161 
#define  OP_LOCKT 160 
#define  OP_LOCKU 159 
#define  OP_LOOKUP 158 
#define  OP_LOOKUPP 157 
#define  OP_NVERIFY 156 
#define  OP_OPEN 155 
#define  OP_OPENATTR 154 
#define  OP_OPEN_CONFIRM 153 
#define  OP_OPEN_DOWNGRADE 152 
#define  OP_PUTFH 151 
#define  OP_PUTPUBFH 150 
#define  OP_PUTROOTFH 149 
#define  OP_READ 148 
#define  OP_READDIR 147 
#define  OP_READLINK 146 
#define  OP_RECLAIM_COMPLETE 145 
#define  OP_RELEASE_LOCKOWNER 144 
#define  OP_REMOVE 143 
#define  OP_RENAME 142 
#define  OP_RENEW 141 
#define  OP_RESTOREFH 140 
#define  OP_SAVEFH 139 
#define  OP_SECINFO 138 
#define  OP_SECINFO_NO_NAME 137 
#define  OP_SEQUENCE 136 
#define  OP_SETATTR 135 
#define  OP_SETCLIENTID 134 
#define  OP_SETCLIENTID_CONFIRM 133 
#define  OP_SET_SSV 132 
#define  OP_TEST_STATEID 131 
#define  OP_VERIFY 130 
#define  OP_WANT_DELEGATION 129 
#define  OP_WRITE 128 

const char* nfs_opnum_to_string(int opnum)
{
    switch (opnum)
    {
    case OP_ACCESS: return "ACCESS";
    case OP_CLOSE: return "CLOSE";
    case OP_COMMIT: return "COMMIT";
    case OP_CREATE: return "CREATE";
    case OP_DELEGPURGE: return "DELEGPURGE";
    case OP_DELEGRETURN: return "DELEGRETURN";
    case OP_GETATTR: return "GETATTR";
    case OP_GETFH: return "GETFH";
    case OP_LINK: return "LINK";
    case OP_LOCK: return "LOCK";
    case OP_LOCKT: return "LOCKT";
    case OP_LOCKU: return "LOCKU";
    case OP_LOOKUP: return "LOOKUP";
    case OP_LOOKUPP: return "LOOKUPP";
    case OP_NVERIFY: return "NVERIFY";
    case OP_OPEN: return "OPEN";
    case OP_OPENATTR: return "OPENATTR";
    case OP_OPEN_CONFIRM: return "OPEN_CONFIRM";
    case OP_OPEN_DOWNGRADE: return "OPEN_DOWNGRADE";
    case OP_PUTFH: return "PUTFH";
    case OP_PUTPUBFH: return "PUTPUBFH";
    case OP_PUTROOTFH: return "PUTROOTFH";
    case OP_READ: return "READ";
    case OP_READDIR: return "READDIR";
    case OP_READLINK: return "READLINK";
    case OP_REMOVE: return "REMOVE";
    case OP_RENAME: return "RENAME";
    case OP_RENEW: return "RENEW";
    case OP_RESTOREFH: return "RESTOREFH";
    case OP_SAVEFH: return "SAVEFH";
    case OP_SECINFO: return "SECINFO";
    case OP_SETATTR: return "SETATTR";
    case OP_SETCLIENTID: return "SETCLIENTID";
    case OP_SETCLIENTID_CONFIRM: return "SETCLIENTID_CONFIRM";
    case OP_VERIFY: return "VERIFY";
    case OP_WRITE: return "WRITE";
    case OP_RELEASE_LOCKOWNER: return "RELEASE_LOCKOWNER";
    case OP_BACKCHANNEL_CTL: return "BACKCHANNEL_CTL";
    case OP_BIND_CONN_TO_SESSION: return "BIND_CONN_TO_SESSION";
    case OP_EXCHANGE_ID: return "EXCHANGE_ID";
    case OP_CREATE_SESSION: return "CREATE_SESSION";
    case OP_DESTROY_SESSION: return "DESTROY_SESSION";
    case OP_FREE_STATEID: return "FREE_STATEID";
    case OP_GET_DIR_DELEGATION: return "GET_DIR_DELEGATION";
    case OP_GETDEVICEINFO: return "GETDEVICEINFO";
    case OP_GETDEVICELIST: return "GETDEVICELIST";
    case OP_LAYOUTCOMMIT: return "LAYOUTCOMMIT";
    case OP_LAYOUTGET: return "LAYOUTGET";
    case OP_LAYOUTRETURN: return "LAYOUTRETURN";
    case OP_SECINFO_NO_NAME: return "SECINFO_NO_NAME";
    case OP_SEQUENCE: return "SEQUENCE";
    case OP_SET_SSV: return "SET_SSV";
    case OP_TEST_STATEID: return "TEST_STATEID";
    case OP_WANT_DELEGATION: return "WANT_DELEGATION";
    case OP_DESTROY_CLIENTID: return "DESTROY_CLIENTID";
    case OP_RECLAIM_COMPLETE: return "RECLAIM_COMPLETE";
    case OP_ILLEGAL: return "ILLEGAL";
    default: return "invalid nfs opnum";
    }
}
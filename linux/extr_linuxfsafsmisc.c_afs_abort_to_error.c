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
typedef  int u32 ;

/* Variables and functions */
#define  AFSVL_BADENTRY 180 
#define  AFSVL_BADINDEX 179 
#define  AFSVL_BADNAME 178 
#define  AFSVL_BADPARTITION 177 
#define  AFSVL_BADREFCOUNT 176 
#define  AFSVL_BADRELLOCKTYPE 175 
#define  AFSVL_BADSERVER 174 
#define  AFSVL_BADSERVERFLAG 173 
#define  AFSVL_BADVOLIDBUMP 172 
#define  AFSVL_BADVOLOPER 171 
#define  AFSVL_BADVOLTYPE 170 
#define  AFSVL_CREATEFAIL 169 
#define  AFSVL_DUPREPSERVER 168 
#define  AFSVL_EMPTY 167 
#define  AFSVL_ENTDELETED 166 
#define  AFSVL_ENTRYLOCKED 165 
#define  AFSVL_IDALREADYHASHED 164 
#define  AFSVL_IDEXIST 163 
#define  AFSVL_IO 162 
#define  AFSVL_NAMEEXIST 161 
#define  AFSVL_NOENT 160 
#define  AFSVL_NOMEM 159 
#define  AFSVL_NOREPSERVER 158 
#define  AFSVL_PERM 157 
#define  AFSVL_REPSFULL 156 
#define  AFSVL_RERELEASE 155 
#define  AFSVL_RWNOTFOUND 154 
#define  AFSVL_SIZEEXCEEDED 153 
 int EACCES ; 
 int EAGAIN ; 
 int EBADRQC ; 
 int EBUSY ; 
 int EDEADLK ; 
 int EDOM ; 
 int EDQUOT ; 
 int EEXIST ; 
 int EFBIG ; 
 int EINVAL ; 
 int EIO ; 
 int EISDIR ; 
 int EKEYEXPIRED ; 
 int EKEYREJECTED ; 
 int EMLINK ; 
 int ENAMETOOLONG ; 
 int ENODEV ; 
 int ENOENT ; 
 int ENOLCK ; 
 int ENOMEDIUM ; 
 int ENOMEM ; 
 int ENOSPC ; 
 int ENOTCONN ; 
 int ENOTDIR ; 
 int ENOTEMPTY ; 
 int ENOTSUPP ; 
 int ENXIO ; 
 int EPERM ; 
 int EPROTO ; 
 int ERANGE ; 
 int EREMOTEIO ; 
 int EROFS ; 
 int ETIMEDOUT ; 
 int EWOULDBLOCK ; 
 int EXDEV ; 
#define  RXGEN_OPCODE 152 
#define  RXKADBADKEY 151 
#define  RXKADBADTICKET 150 
#define  RXKADDATALEN 149 
#define  RXKADEXPIRED 148 
#define  RXKADILLEGALLEVEL 147 
#define  RXKADINCONSISTENCY 146 
#define  RXKADLEVELFAIL 145 
#define  RXKADNOAUTH 144 
#define  RXKADOUTOFSEQUENCE 143 
#define  RXKADPACKETSHORT 142 
#define  RXKADSEALEDINCON 141 
#define  RXKADTICKETLEN 140 
#define  RXKADUNKNOWNKEY 139 
#define  VBUSY 138 
#define  VDISKFULL 137 
#define  VMOVED 136 
#define  VNOSERVICE 135 
#define  VNOVNODE 134 
#define  VNOVOL 133 
#define  VOFFLINE 132 
#define  VONLINE 131 
#define  VOVERQUOTA 130 
#define  VSALVAGE 129 
#define  VVOLEXISTS 128 

int afs_abort_to_error(u32 abort_code)
{
	switch (abort_code) {
		/* Low errno codes inserted into abort namespace */
	case 13:		return -EACCES;
	case 27:		return -EFBIG;
	case 30:		return -EROFS;

		/* VICE "special error" codes; 101 - 111 */
	case VSALVAGE:		return -EIO;
	case VNOVNODE:		return -ENOENT;
	case VNOVOL:		return -ENOMEDIUM;
	case VVOLEXISTS:	return -EEXIST;
	case VNOSERVICE:	return -EIO;
	case VOFFLINE:		return -ENOENT;
	case VONLINE:		return -EEXIST;
	case VDISKFULL:		return -ENOSPC;
	case VOVERQUOTA:	return -EDQUOT;
	case VBUSY:		return -EBUSY;
	case VMOVED:		return -ENXIO;

		/* Volume Location server errors */
	case AFSVL_IDEXIST:		return -EEXIST;
	case AFSVL_IO:			return -EREMOTEIO;
	case AFSVL_NAMEEXIST:		return -EEXIST;
	case AFSVL_CREATEFAIL:		return -EREMOTEIO;
	case AFSVL_NOENT:		return -ENOMEDIUM;
	case AFSVL_EMPTY:		return -ENOMEDIUM;
	case AFSVL_ENTDELETED:		return -ENOMEDIUM;
	case AFSVL_BADNAME:		return -EINVAL;
	case AFSVL_BADINDEX:		return -EINVAL;
	case AFSVL_BADVOLTYPE:		return -EINVAL;
	case AFSVL_BADSERVER:		return -EINVAL;
	case AFSVL_BADPARTITION:	return -EINVAL;
	case AFSVL_REPSFULL:		return -EFBIG;
	case AFSVL_NOREPSERVER:		return -ENOENT;
	case AFSVL_DUPREPSERVER:	return -EEXIST;
	case AFSVL_RWNOTFOUND:		return -ENOENT;
	case AFSVL_BADREFCOUNT:		return -EINVAL;
	case AFSVL_SIZEEXCEEDED:	return -EINVAL;
	case AFSVL_BADENTRY:		return -EINVAL;
	case AFSVL_BADVOLIDBUMP:	return -EINVAL;
	case AFSVL_IDALREADYHASHED:	return -EINVAL;
	case AFSVL_ENTRYLOCKED:		return -EBUSY;
	case AFSVL_BADVOLOPER:		return -EBADRQC;
	case AFSVL_BADRELLOCKTYPE:	return -EINVAL;
	case AFSVL_RERELEASE:		return -EREMOTEIO;
	case AFSVL_BADSERVERFLAG:	return -EINVAL;
	case AFSVL_PERM:		return -EACCES;
	case AFSVL_NOMEM:		return -EREMOTEIO;

		/* Unified AFS error table; ET "uae" == 0x2f6df00 */
	case 0x2f6df00:		return -EPERM;
	case 0x2f6df01:		return -ENOENT;
	case 0x2f6df04:		return -EIO;
	case 0x2f6df0a:		return -EAGAIN;
	case 0x2f6df0b:		return -ENOMEM;
	case 0x2f6df0c:		return -EACCES;
	case 0x2f6df0f:		return -EBUSY;
	case 0x2f6df10:		return -EEXIST;
	case 0x2f6df11:		return -EXDEV;
	case 0x2f6df12:		return -ENODEV;
	case 0x2f6df13:		return -ENOTDIR;
	case 0x2f6df14:		return -EISDIR;
	case 0x2f6df15:		return -EINVAL;
	case 0x2f6df1a:		return -EFBIG;
	case 0x2f6df1b:		return -ENOSPC;
	case 0x2f6df1d:		return -EROFS;
	case 0x2f6df1e:		return -EMLINK;
	case 0x2f6df20:		return -EDOM;
	case 0x2f6df21:		return -ERANGE;
	case 0x2f6df22:		return -EDEADLK;
	case 0x2f6df23:		return -ENAMETOOLONG;
	case 0x2f6df24:		return -ENOLCK;
	case 0x2f6df26:		return -ENOTEMPTY;
	case 0x2f6df28:		return -EWOULDBLOCK;
	case 0x2f6df69:		return -ENOTCONN;
	case 0x2f6df6c:		return -ETIMEDOUT;
	case 0x2f6df78:		return -EDQUOT;

		/* RXKAD abort codes; from include/rxrpc/packet.h.  ET "RXK" == 0x1260B00 */
	case RXKADINCONSISTENCY: return -EPROTO;
	case RXKADPACKETSHORT:	return -EPROTO;
	case RXKADLEVELFAIL:	return -EKEYREJECTED;
	case RXKADTICKETLEN:	return -EKEYREJECTED;
	case RXKADOUTOFSEQUENCE: return -EPROTO;
	case RXKADNOAUTH:	return -EKEYREJECTED;
	case RXKADBADKEY:	return -EKEYREJECTED;
	case RXKADBADTICKET:	return -EKEYREJECTED;
	case RXKADUNKNOWNKEY:	return -EKEYREJECTED;
	case RXKADEXPIRED:	return -EKEYEXPIRED;
	case RXKADSEALEDINCON:	return -EKEYREJECTED;
	case RXKADDATALEN:	return -EKEYREJECTED;
	case RXKADILLEGALLEVEL:	return -EKEYREJECTED;

	case RXGEN_OPCODE:	return -ENOTSUPP;

	default:		return -EREMOTEIO;
	}
}
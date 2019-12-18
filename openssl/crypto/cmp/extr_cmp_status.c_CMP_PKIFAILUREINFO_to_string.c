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
#define  OSSL_CMP_PKIFAILUREINFO_addInfoNotAvailable 154 
#define  OSSL_CMP_PKIFAILUREINFO_badAlg 153 
#define  OSSL_CMP_PKIFAILUREINFO_badCertId 152 
#define  OSSL_CMP_PKIFAILUREINFO_badCertTemplate 151 
#define  OSSL_CMP_PKIFAILUREINFO_badDataFormat 150 
#define  OSSL_CMP_PKIFAILUREINFO_badMessageCheck 149 
#define  OSSL_CMP_PKIFAILUREINFO_badPOP 148 
#define  OSSL_CMP_PKIFAILUREINFO_badRecipientNonce 147 
#define  OSSL_CMP_PKIFAILUREINFO_badRequest 146 
#define  OSSL_CMP_PKIFAILUREINFO_badSenderNonce 145 
#define  OSSL_CMP_PKIFAILUREINFO_badTime 144 
#define  OSSL_CMP_PKIFAILUREINFO_certConfirmed 143 
#define  OSSL_CMP_PKIFAILUREINFO_certRevoked 142 
#define  OSSL_CMP_PKIFAILUREINFO_duplicateCertReq 141 
#define  OSSL_CMP_PKIFAILUREINFO_incorrectData 140 
#define  OSSL_CMP_PKIFAILUREINFO_missingTimeStamp 139 
#define  OSSL_CMP_PKIFAILUREINFO_notAuthorized 138 
#define  OSSL_CMP_PKIFAILUREINFO_signerNotTrusted 137 
#define  OSSL_CMP_PKIFAILUREINFO_systemFailure 136 
#define  OSSL_CMP_PKIFAILUREINFO_systemUnavail 135 
#define  OSSL_CMP_PKIFAILUREINFO_timeNotAvailable 134 
#define  OSSL_CMP_PKIFAILUREINFO_transactionIdInUse 133 
#define  OSSL_CMP_PKIFAILUREINFO_unacceptedExtension 132 
#define  OSSL_CMP_PKIFAILUREINFO_unacceptedPolicy 131 
#define  OSSL_CMP_PKIFAILUREINFO_unsupportedVersion 130 
#define  OSSL_CMP_PKIFAILUREINFO_wrongAuthority 129 
#define  OSSL_CMP_PKIFAILUREINFO_wrongIntegrity 128 

__attribute__((used)) static const char *CMP_PKIFAILUREINFO_to_string(int number)
{
    switch (number) {
    case OSSL_CMP_PKIFAILUREINFO_badAlg:
        return "badAlg";
    case OSSL_CMP_PKIFAILUREINFO_badMessageCheck:
        return "badMessageCheck";
    case OSSL_CMP_PKIFAILUREINFO_badRequest:
        return "badRequest";
    case OSSL_CMP_PKIFAILUREINFO_badTime:
        return "badTime";
    case OSSL_CMP_PKIFAILUREINFO_badCertId:
        return "badCertId";
    case OSSL_CMP_PKIFAILUREINFO_badDataFormat:
        return "badDataFormat";
    case OSSL_CMP_PKIFAILUREINFO_wrongAuthority:
        return "wrongAuthority";
    case OSSL_CMP_PKIFAILUREINFO_incorrectData:
        return "incorrectData";
    case OSSL_CMP_PKIFAILUREINFO_missingTimeStamp:
        return "missingTimeStamp";
    case OSSL_CMP_PKIFAILUREINFO_badPOP:
        return "badPOP";
    case OSSL_CMP_PKIFAILUREINFO_certRevoked:
        return "certRevoked";
    case OSSL_CMP_PKIFAILUREINFO_certConfirmed:
        return "certConfirmed";
    case OSSL_CMP_PKIFAILUREINFO_wrongIntegrity:
        return "wrongIntegrity";
    case OSSL_CMP_PKIFAILUREINFO_badRecipientNonce:
        return "badRecipientNonce";
    case OSSL_CMP_PKIFAILUREINFO_timeNotAvailable:
        return "timeNotAvailable";
    case OSSL_CMP_PKIFAILUREINFO_unacceptedPolicy:
        return "unacceptedPolicy";
    case OSSL_CMP_PKIFAILUREINFO_unacceptedExtension:
        return "unacceptedExtension";
    case OSSL_CMP_PKIFAILUREINFO_addInfoNotAvailable:
        return "addInfoNotAvailable";
    case OSSL_CMP_PKIFAILUREINFO_badSenderNonce:
        return "badSenderNonce";
    case OSSL_CMP_PKIFAILUREINFO_badCertTemplate:
        return "badCertTemplate";
    case OSSL_CMP_PKIFAILUREINFO_signerNotTrusted:
        return "signerNotTrusted";
    case OSSL_CMP_PKIFAILUREINFO_transactionIdInUse:
        return "transactionIdInUse";
    case OSSL_CMP_PKIFAILUREINFO_unsupportedVersion:
        return "unsupportedVersion";
    case OSSL_CMP_PKIFAILUREINFO_notAuthorized:
        return "notAuthorized";
    case OSSL_CMP_PKIFAILUREINFO_systemUnavail:
        return "systemUnavail";
    case OSSL_CMP_PKIFAILUREINFO_systemFailure:
        return "systemFailure";
    case OSSL_CMP_PKIFAILUREINFO_duplicateCertReq:
        return "duplicateCertReq";
    default:
        return NULL; /* illegal failure number */
    }
}